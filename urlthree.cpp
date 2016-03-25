#include "urlthree.h"

URLThree::URLThree(QObject *parent) : QObject(parent)
{
    progress = 0;

}

void URLThree::start_scan()
{
    emit message_to_log("Start scan");
    emit message_to_find("Find");
    emit update_progress(progress++);
}

void URLThree::set_main_window(Ui::MainWindow *ui)
{
    this->ui = ui;
}

