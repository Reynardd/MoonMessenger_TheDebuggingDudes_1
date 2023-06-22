#ifndef CHADTHREAD_H
#define CHADTHREAD_H

#include <QObject>

class ChadThread : public QObject
{
    Q_OBJECT
public:
    explicit ChadThread(QObject *parent = nullptr);

signals:

};

#endif // CHADTHREAD_H
