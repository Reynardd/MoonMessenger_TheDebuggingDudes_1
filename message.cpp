#include "message.h"

Message::Message(int id,QString sender,QString text,QString date,QObject *parent)
    : QObject{parent}
{
    _id = id;
    _sender = sender;
    _text = text;
    _date = date;
}
Message::Message(QString data,QObject* parent) : QObject{parent}
{
    QTextStream stream(&data);
    _id = stream.readLine().toInt();
    _sender = stream.readLine();
    _date = stream.readLine();
    _text = stream.readAll();
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
QString Message::toString()
{
    QString res;
    res+= QString::number(_id) + "\n";
    res+= _sender + "\n";
    res+= _date+ "\n";
    res+= _text+"\n";
    res+= "MM:ENDOFMESSAGE\n";
    return res;
}

