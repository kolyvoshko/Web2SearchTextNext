#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    th = new StartThread;

    ui->setupUi(this);

    ui->progressBar->setValue(0);

    ui->spinBox_max_url->setValue(1);
    ui->spinBox_max_url->setMinimum(1);
    ui->spinBox_max_url->setMaximum(10000);

    ui->spinBox_number_scan_theads->setValue(1);
    ui->spinBox_number_scan_theads->setMinimum(1);
    ui->spinBox_number_scan_theads->setMaximum(1000);

    ui->lineEdit_url->setText("https://www.gentoo.org/");
    ui->plainTextEdit_search_text->appendPlainText("Gentoo");

    // for find end log browsers
    html_style = "<style>"
                 "p.find{color: green; margin: 0; padding: 0;}"
                 "p.error{color: red; margin: 0; padding: 0;}"
                 "</style>";

    format_find = "<p class=\"find\">%1</p>";
    format_error = "<p class=\"error\">%1</p>";


    ui->textBrowser_find->setHtml(html_style);
    ui->textBrowser_log->setHtml(html_style);

    connect(ui->pushButton_start, SIGNAL(clicked()), this, SLOT(start_slot()));
    connect(ui->pushButton_pause, SIGNAL(clicked()), th->tree, SLOT(pause_slot()));
    connect(ui->pushButton_stop, SIGNAL(clicked()), th->tree, SLOT(stop_slot()));

    connect(th->tree, SIGNAL(update_progress(int)), ui->progressBar, SLOT(setValue(int)));

    connect(th->tree, SIGNAL(message_to_log(QString)), ui->textBrowser_log,   SLOT(append(QString)));
    connect(th->tree, SIGNAL(message_to_find(QString)), ui->textBrowser_find, SLOT(append(QString)));

    connect(th->tree, SIGNAL(html_to_find_browser(QString,QString)), this, SLOT(html_to_find_browser(QString,QString)));
    connect(th->tree, SIGNAL(html_to_log_browser(QString,QString)),  this, SLOT(html_to_log_browser(QString,QString)));

    connect(ui->actionExit, SIGNAL(triggered(bool)), this->window(), SLOT(close()));
    connect(ui->actionFull_screen, SIGNAL(triggered(bool)), this->window(), SLOT(showFullScreen()));
    connect(ui->actionMaximize, SIGNAL(triggered(bool)), this->window(), SLOT(showMaximized()));
    connect(ui->actionMinimize, SIGNAL(triggered(bool)), this->window(), SLOT(showMinimized()));
    connect(ui->actionHide, SIGNAL(triggered(bool)), this->window(), SLOT(setHidden(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start_slot()
{
    if (th->isRunning())
        th->tree->pause_slot();

    else
    {
    ui->textBrowser_find->clear();
    ui->textBrowser_log->clear();

    th->tree->set_find_text(ui->plainTextEdit_search_text->toPlainText());
    th->tree->set_start_url(ui->lineEdit_url->text());
    th->tree->set_max_number_threads(ui->spinBox_number_scan_theads->value());
    th->tree->set_max_scan_url(ui->spinBox_max_url->value());
    th->start();
    }
}

void MainWindow::html_to_find_browser(QString type, QString info)
{
    if (type == "find")
        ui->textBrowser_find->append(html_style + format_find.arg(info));

    else if (type == "error")
        ui->textBrowser_find->append(html_style + format_error.arg(info));

    else
       ui->textBrowser_find->append(html_style + info);
}

void MainWindow::html_to_log_browser(QString type, QString info)
{
    if (type == "find")
        ui->textBrowser_log->append(html_style + format_find.arg(info));

    else if (type == "error")
        ui->textBrowser_log->append(html_style + format_error.arg(info));

    else
       ui->textBrowser_log->append(html_style + info);
}
