#include "conversation.h"
Conversation::Conversation(QString name,QString type,QObject *parent)
    : QObject{parent}
{
    _name = name;
    chatType = type;
    _messageCount = 0;
}
