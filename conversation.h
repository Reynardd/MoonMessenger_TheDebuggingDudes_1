#ifndef CONVERSATION_H
#define CONVERSATION_H
#include "message.h"
#include "request.h"
#include <QObject>
#include <vector>
using namespace std;
class Conversation : public QObject
{
    Q_OBJECT
public:
    explicit Conversation(QString _name,QString type,QObject *parent = nullptr);
    ~Conversation();
    QString toString();
    void getUpdate(QString token);
    const QString& name();
    const QString& type();
    QString lastDate();
    void show_conversation();
private:
    QString _name;
    int messageCount;
    QString chatType;
    vector<Message*> messages;
signals:
    void getUpdate_failed();
    void connection_lost();
    void session_expired();
    void newMessage_arrived();
};

#endif // CONVERSATION_H
