#ifndef URLTREE_H
#define URLTREE_H

#include <QObject>

/**
 * @brief The URLTree class has utl three and can run scaning url three
 */
class URLTree : public QObject
{
    Q_OBJECT

public:
    explicit URLTree(QObject *parent = 0);

    void start_scan(); /// @brief start_scan start scan url three

signals:
    void message_to_log(QString info);  /// @brief append the text to log text browser
    void message_to_find(QString info); /// @brief append the text to findlist text browser
    void update_progress(int value);    /// @brief update progressBar value

public slots:
    void start_slot();
    void pause_slot(){if_pause = if_pause?false:true;}
    void stop_slot(){this->if_stop = true;}

    void set_find_text(QString text){this->find_text = text;}
    void set_start_url(QString url){this->start_url = url;}
    void set_max_number_threads(int number){this->max_number_threads = number;}
    void set_max_scan_url(int number){this->max_scan_url = number;}

private:
    int progress;           /// @brief progressBar value: [0, 100]
    int max_number_threads; /// @brief max number of threads: [1,...]
    int max_scan_url;       /// @brief max number of scanning url: [1,...]

    QString start_url; /// @brief start url
    QString find_text; /// @brief find this text in html code

    bool if_pause; /// @brief if true - pause scanning, if false - continue
    bool if_stop;  /// @brief if true - stop scanning, if false continue
};

#endif // URLTREE_H
