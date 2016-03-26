#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "startthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    StartThread *th;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    /**
     * @brief start_slot Start scanning url
     */
    void start_slot();
};

#endif // MAINWINDOW_H
