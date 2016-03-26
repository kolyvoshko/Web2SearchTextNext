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

    QString html_style;     /// text html style in text browser
    QString format_find;    /// html format for find messages
    QString format_error;   /// html format for error messages

private slots:
    /**
     * @brief start_slot Start scanning url
     */
    void start_slot();

    void html_to_find_browser(QString type, QString info);
    void html_to_log_browser(QString type, QString info);
};

#endif // MAINWINDOW_H
