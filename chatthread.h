#ifndef CHATTHREAD_H
#define CHATTHREAD_H

#include <QObject>
#include "user.h"
using namespace std;
#include <functional>
typedef function<void()> Func;
class ChatThread : public QObject
{
    Q_OBJECT
public:
    explicit ChatThread(User* user,QObject *parent = nullptr);
    ~ChatThread();
    void start();
    void stop();
private:
    vector<Func> updaters;
    void check_new_user();
    void check_new_channel();
    void check_new_group();
    void check_new(QString type);
    bool running;
    User* user;
private slots:
    void connectionLost();
signals:
    void sessionExpired();

};

#endif // CHATTHREAD_H
