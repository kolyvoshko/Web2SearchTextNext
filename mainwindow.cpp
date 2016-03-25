#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);

    start_thread = new StartThread;

    connect(ui->pushButton, SIGNAL (clicked()), this, SLOT (start()));
    connect(start_thread->three, SIGNAL (call_message(QString)), this, SLOT (messager(QString)));
    connect(start_thread->three, SIGNAL (update_progress(int)), ui->progressBar, SLOT (setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start()
{
    ui->textBrowser->append("Start");
    start_thread->start();

}

void MainWindow::messager(QString info)
{
    ui->textBrowser->append(info);
}
