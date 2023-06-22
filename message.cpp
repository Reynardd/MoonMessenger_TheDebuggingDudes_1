#include "message.h"

Message::Message(QString sender,QString text,QString date,QObject *parent)
    : QObject{parent}
{
    _sender = sender;
    _text = text;
    _date = date;
}

Message::Message(Message &m)
{
    _sender = m._sender;
    _text = m._text;
    _date = m._date;
}
QString Message::date()
{
    return _date;
}
Message::~Message()
{

}
