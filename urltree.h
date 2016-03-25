#ifndef URLTHREE_H
#define URLTHREE_H

#include <QObject>

class URLThree : public QObject
{
    Q_OBJECT

public:
    explicit URLThree(QObject *parent = 0);
    void start_scan();

signals:
    void message_to_log(QString info);
    void message_to_find(QString info);

    void update_progress(int value);

public slots:
    void start_slot(){this->start_scan();}
    void pause_slot(){}
    void stop_slot(){}

    void set_find_text(QString text){this->find_text = text;}
    void set_start_url(QString url){this->start_url = url;}
    void set_max_number_threads(int number){this->max_number_threads = number;}
    void set_max_scan_url(int number){this->max_scan_url = number;}

private:
    int progress;
    int max_number_threads;
    int max_scan_url;

    QString start_url;
    QString find_text;
};

#endif // URLTHREE_H
