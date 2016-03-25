#ifndef STARTTHREAD_H
#define STARTTHREAD_H

#include <QThread>

#include "urltree.h"

class StartThread : public QThread
{
public:
    StartThread();

    void run()
    {

    }

    URLTree *tree;
};

#endif // STARTTHREAD_H
