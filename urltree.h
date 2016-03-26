#ifndef URLTREE_H
#define URLTREE_H

#include <QObject>
#include <QThreadPool>
#include <QFutureSynchronizer>

#include <queue>

/**
 * @brief The Node struct has information about url page
 */
struct Node
{
    Node()
    {
        is_find_text = false;
        is_scan = false;
    }

    bool is_find_text; /// if tint text - true
    bool is_scan;      /// if scaned    - true

    std::string url;    /// node url
    std::list<Node *> children;
};

/**
 * @brief The URLTree class has utl three and can run scaning url three
 */
class URLTree : public QThread
{
    Q_OBJECT

public:
    explicit URLTree(QThread *parent = 0);

    void start_scan(); /// @brief start_scan start scan url three

signals:
    void message_to_log(QString info);  /// @brief append the text to log text browser
    void message_to_find(QString info); /// @brief append the text to findlist text browser
    void update_progress(int value);    /// @brief update progressBar value

    void html_to_find_browser(QString type, QString info); /// @brief append the html code to find text browser
    void html_to_log_browser(QString type, QString info);  /// @brief append the html code to log text browser

public slots:
    void start_slot();
    void pause_slot(){if_pause = if_pause?false:true;}
    void stop_slot(){this->if_stop = true;}

    void set_find_text(QString text){this->find_text = text.toUtf8().constData();}
    void set_start_url(QString url){this->start_url = url.toUtf8().constData();}
    void set_max_number_threads(int number){this->max_number_threads = number;}
    void set_max_scan_url(int number){this->max_scan_url = number;}

private:
    Node * root; /// Root node in url tree
    QFutureSynchronizer<void> synchronizer;

    int process_bar_count;  /// @brief progressBar value: [0, 100]
    int max_number_threads; /// @brief max number of threads: [1,...]
    int max_scan_url;       /// @brief max number of scanning url: [1,...]
    int current_scan_urls;  /// @brief current scaned urls: [1, max_scan_url]

    std::string start_url; /// @brief start url
    std::string find_text; /// @brief find this text in html code

    bool if_pause; /// @brief if true - pause scanning, if false - continue
    bool if_stop;  /// @brief if true - stop scanning, if false continue


    /**
     * @brief scan_node scan one node and all not find url to node->childs
     * @param node: scanning node
     */
    void scan_node(std::queue<Node *> *nextLevel, Node * node);


    /**
     * @brief find_node find node that has url addres equal url
     * @param url url address
     * @return if find -> true
     */
    bool find_node(std::string *url);

    /**
     * @brief update parameters after done
     */
    void update();
};

#endif // URLTREE_H
