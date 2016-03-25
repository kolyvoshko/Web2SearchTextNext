#ifndef URLTHREE_H
#define URLTHREE_H

#include <QObject>

class URLThree : public QObject
{
    Q_OBJECT

    int progress;

public:
    explicit URLThree(QObject *parent = 0);
    void start_scan();

signals:
    void call_message(QString info);
    void update_progress(int value);

public slots:
};

#endif // URLTHREE_H
