#include "urltree.h"

URLTree::URLTree(QObject *parent) : QObject(parent)
{
    progress = 0;
    max_scan_url = 1;
    max_number_threads = 1;

    if_pause = false;
    if_stop = false;
}

void URLTree::start_scan()
{
    emit message_to_log("log");
    emit message_to_find("find");
    emit update_progress(progress++);
}

void URLTree::start_slot()
{
    this->if_stop = false;
    this->if_pause = false;
    this->start_scan();
}


