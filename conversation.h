#ifndef CONVERSATION_H
#define CONVERSATION_H
#include "message.h"
#include <QObject>
class Conversation : public QObject
{
    Q_OBJECT
public:
    explicit Conversation(QString _name,QString type,QObject *parent = nullptr);
    QString toString();
private:
    QString _name;
    int _messageCount;
    QString chatType;
    QVector<Message> messages;
signals:

};

#endif // CONVERSATION_H
