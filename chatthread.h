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
    void setLayout(QLayout* layout);
    bool isRunning();
private:
    QLayout* layout;
    void check_new_user();
    void check_new_channel();
    void check_new_group();
    QThreadPool threadPool;
    void check_new(QString type);
    bool running;
    User* user;
signals:
    void sessionExpired();
    void connectionLost();
    void invalidResponse(QString);

};

#endif // CHATTHREAD_H
