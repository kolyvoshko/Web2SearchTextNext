#include "urlthree.h"

URLThree::URLThree(QObject *parent) : QObject(parent)
{
    progress = 0;
    max_scan_url = 1;
    max_number_threads = 1;
}

void URLThree::start_scan()
{
    emit message_to_log("log");
    emit message_to_find("find");
    emit update_progress(progress++);
}


