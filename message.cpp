#include "message.h"

Message::Message(int id,QString sender,QString text,QString date,QObject *parent)
    : QObject{parent}
{
    _id = id;
    _sender = sender;
    _text = text;
    _date = date;
}

Message::Message(Message &m)
{
    _id = m._id;
    _sender = m._sender;
    _text = m._text;
    _date = m._date;
}
QString Message::date()
{
    return _date;
}
