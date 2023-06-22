#include "message.h"

Message::Message(QString sender,QString text,QString date,QObject *parent)
    : QObject{parent}
{
    _sender = sender;
    _text = text;
    _date = date;
}
QString Message::date()
{
    return _date;
}
