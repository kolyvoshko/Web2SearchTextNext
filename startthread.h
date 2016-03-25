#ifndef STARTTHREAD_H
#define STARTTHREAD_H

#include <QThread>

#include "urlthree.h"

class StartThread : public QThread
{
public:
    StartThread();

    void run()
    {
        three->start_scan();
    }

    URLThree *three;
};

#endif // STARTTHREAD_H
