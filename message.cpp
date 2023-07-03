#include "message.h"
#include <QDebug>
Message::Message(int id,QString sender,QString text,QString date,QObject *parent)
    : QObject{parent}
{
    _id = id;
    _sender = sender;
    _text = text;
    _date = date;
    connect(this,&Message::wasLiked,this,&Message::toggleLiked);
    connect(this,SIGNAL(deleted()),this,SLOT(deleteMessage()));
    isLiked = false;
    isDeleted = false;
}
Message::Message(QString data,QObject* parent) : QObject{parent}
{
    QTextStream stream(&data);
    _id = stream.readLine().toInt();
    _sender = stream.readLine();
    _date = stream.readLine();
    _text = stream.readAll();
    isLiked = false;
    isDeleted = false;
    connect(this,&Message::wasLiked,this,&Message::toggleLiked);
    connect(this,SIGNAL(deleted()),this,SLOT(deleteMessage()));
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
QString Message::sender()
{
    return _sender;
}
QString Message::text()
{
    return _text;
}
const int& Message::id() { return _id; }

void Message::toggleLiked()
{
    if(isLiked){isLiked = false;}
    else {isLiked = true;}

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
QString Message::type()
{
    if(this->_text.startsWith("#SERVERCOMMAND-LIKE")){ return "like";}
    if(this->_text.startsWith("#SERVERCOMMAND-DELETE")){ return "delete";}
    return "text";
}
void Message::deleteMessage()
{
    isDeleted = true;
}
