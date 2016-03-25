#include "urlthree.h"

URLThree::URLThree(QObject *parent) : QObject(parent)
{
    progress = 0;
}

void URLThree::start_scan()
{
    emit call_message("Start scan");
    emit update_progress(progress++);
}

