#ifndef STARTTHREAD_H
#define STARTTHREAD_H

#include <QThread>
#include "ui_mainwindow.h"

#include "urlthree.h"

class StartThread : public QThread
{
public:
    StartThread();

    void send_main_window(Ui::MainWindow *ui)
    {
        tree->set_main_window(ui);
    }

    void run()
    {

    }

    URLThree *tree;
};

#endif // STARTTHREAD_H
