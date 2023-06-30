#ifndef CHATTHREAD_H
#define CHATTHREAD_H

#include <QObject>
#include "user.h"
#include <QLayout>
#include <QThreadPool>
using namespace std;
#include <functional>
class ChatThread : public QObject
{
    Q_OBJECT
public:
    explicit ChatThread(User* user,QObject *parent = nullptr);
    ~ChatThread();
    void start();
    void stop();
    bool isRunning();
private:
    void check_new_user();
    void check_new_channel();
    void check_new_group();
    void run();
    QThreadPool threadPool;
    void check_new(QString type);
    bool running;
    User* user;
signals:
    void sessionExpired();
    void connectionLost();
    void invalidResponse(QString);
    void isStopped(bool);

};

#endif // CHATTHREAD_H
