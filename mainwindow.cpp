#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);

    th = new StartThread;

    connect(ui->pushButton_start, SIGNAL (clicked()), this, SLOT (start_slot()));

    connect(ui->pushButton_pause, SIGNAL (clicked()), th->tree, SLOT (pause_slot()));
    connect(ui->pushButton_stop, SIGNAL (clicked()), th->tree, SLOT (stop_slot()));

    connect(th->tree, SIGNAL (message_to_log(QString)), ui->textBrowser_log, SLOT (append(QString)));
    connect(th->tree, SIGNAL (message_to_find(QString)), ui->textBrowser_find, SLOT (append(QString)));

    connect(th->tree, SIGNAL (update_progress(int)), ui->progressBar, SLOT (setValue(int)));

    th->start();
    th->send_main_window(ui);
}

MainWindow::~MainWindow()
{
    delete ui;
}
