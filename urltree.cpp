#include "urltree.h"

#include <QtConcurrentRun>
#include <list>
#include <queue>
#include <string>

#include "url_util.h"

URLTree::URLTree(QThread *parent) : QThread(parent)
{
    process_bar_count = 0;

    max_scan_url = 1;
    current_scan_urls = 0;

    max_number_threads = 1;

    if_pause = false;
    if_stop = false;

    this->root = new Node;
}

void URLTree::start_scan()
{
    QThreadPool::globalInstance()->setMaxThreadCount(max_number_threads);

    if (!root)
        return;

    root->url = this->start_url;

    std::queue<Node *> current, next;
    current.push(root);

    while (!current.empty())
    {
        if (if_pause)
        {
            //msleep(100);
            continue;
        }
        if (if_stop)
        {
            synchronizer.waitForFinished();
            break;
        }

        if (QThreadPool::globalInstance()->activeThreadCount() <
                QThreadPool::globalInstance()->maxThreadCount())
        {
            current_scan_urls++;
            std::cout << QThreadPool::globalInstance()->activeThreadCount() << std::endl;

            if (current_scan_urls + QThreadPool::globalInstance()->activeThreadCount() > max_scan_url)
            {
                synchronizer.waitForFinished();
                break;
            }

            process_bar_count = (100*this->current_scan_urls)/this->max_scan_url;
            emit update_progress(process_bar_count);

            Node *current_node = current.front();
            current.pop();

            synchronizer.addFuture( QtConcurrent::run( this, &URLTree::scan_node, &next, current_node) );
        }

        if (current.empty())
        {
            synchronizer.waitForFinished();
            msleep(200);
            std::swap(current, next);
        }
    }

    this->update(); // clear data objects
}


void URLTree::scan_node(std::queue<Node *> *nextLevel, Node *node)
{
    if (node->is_scan)
        return;

    else node->is_scan = true;

    std::string curl_type_message;
    std::string curl_message;

    std::string html_code(download_html(node->url.c_str(), &curl_type_message, &curl_message) );
    node->is_find_text = find_string(&html_code, &this->find_text);


    std::string is_find = node->is_find_text ? "true" : "false";
    std::string log_type_message = node->is_find_text ? "find" : "log";


    if (curl_type_message == "error")
        log_type_message = "error";

    emit html_to_log_browser(QString::fromStdString(log_type_message),
                             QString::fromStdString("URL: " + node->url
                                                    + "\t"+ "Find text: " + is_find + "\n "
                                                    + curl_message));

    if (node->is_find_text){
        // out to stdout
        std::cout << std::boolalpha << "Find text \"" <<
              this->find_text << "\": "<< node->is_find_text << std::endl;

        std::cout << "URL: " << node->url << std::endl << std::endl;

        // redirect to gui text browsers
        emit html_to_find_browser("find", QString::fromStdString(node->url));
    }


    std::list<std::string> urls = find_url(&html_code);

    for (auto it : urls)
    {
        bool is_find = this->find_node(&it);

        if (!is_find)
        {
            emit message_to_log(QString::fromStdString("Find new url: " + it));

            Node * add_node = new Node;
            add_node->url = it;
            node->childs.push_back(add_node);
        }
    }

    if (!node->childs.empty())
    {
        for (auto &it : node->childs)
            nextLevel->push(it);
    }
}


bool URLTree::find_node(std::string * url)
{
    if (!root)
        return false;

    std::queue<Node *> current, next;
    current.push(root);

    while (!current.empty())
    {
        Node *current_node = current.front();
        current.pop();

        if (current_node->url == *url)
            return true;

        if (!current_node->childs.empty())
        {
            for (auto &it : current_node->childs)
                next.push(it);
        }

        if (current.empty())
            std::swap(current, next);
    }

    return false;
}

void URLTree::update()
{
    this->process_bar_count = 0;
    this->current_scan_urls = 0;
    delete root;
    root = new Node;
}


void URLTree::start_slot()
{
    this->if_stop = false;
    this->if_pause = false;
    this->start_scan();
}


