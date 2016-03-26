#ifndef STARTTHREAD_H
#define STARTTHREAD_H

#include <QThread>

#include "urltree.h"

/**
 * @brief The StartThread class start URLTree object in own QThread
 */
class StartThread : public QThread
{
public:
    StartThread();

    void run(){tree->start_slot();}

    URLTree *tree;
};

#endif // STARTTHREAD_H
