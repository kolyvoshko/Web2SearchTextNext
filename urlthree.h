#ifndef URLTHREE_H
#define URLTHREE_H

#include <QObject>
#include "ui_mainwindow.h"

class URLThree : public QObject
{
    Q_OBJECT

    int progress;
    Ui::MainWindow *ui;

public:
    explicit URLThree(QObject *parent = 0);
    void start_scan();
    void set_main_window(Ui::MainWindow *ui);

signals:
    void message_to_log(QString info);
    void message_to_find(QString info);

    void update_progress(int value);

public slots:
    void start_slot(){this->start_scan();}
    void pause_slot(){}
    void stop_slot(){}
};

#endif // URLTHREE_H
