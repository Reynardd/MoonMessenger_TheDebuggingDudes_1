#include "conversation.h"
#include <QRegularExpression>
#include "infodialog.h"
#include <QTextStream>
#include "conversationwindow.h"
#include <algorithm>
extern User* user;
Conversation::Conversation(QString name,QString type,QString token,QObject *parent)
    : QObject{parent}
{
    _name = name;
    chatType = type;
    messageCount = 0;
    this->getUpdate(token);
}
Conversation::Conversation(QString data, QObject* parent) : QObject{parent}
{
    QTextStream stream(&data);
    chatType = stream.readLine();
    messageCount = stream.readLine().toInt();
    _name = stream.readLine();
    QString buffer;
    QString message;
    while(!stream.atEnd())
    {
        buffer = stream.readLine();

        if(buffer=="MM:ENDOFMESSAGE")
        {

            Message* mes = new Message(message);
            messages.push_back(mes);
            message.clear();
            if(mes->type()=="like")
            {
                QString id = mes->text().replace("#SERVERCOMMAND-LIKE","").replace("\n","");
                for(Message* m:messages)
                {
                    if(m->id()==id.toInt()) { emit m->wasLiked();break;}
                }
            }


            if(mes->type()=="delete")
            {
                QString id = mes->text().replace("#SERVERCOMMAND-DELETE","").replace("\n","");
                for(Message* m:messages)
                {
                    if(m->id()==id.toInt())
                    {
                        emit m->deleted();;
                    }
                }
            }

        }
        else
        {
            message+=buffer+"\n";
        }
    }
}
QString Conversation::lastDate()
{
    QString date = messages[messageCount-1]->date();
    QString fDate =  date.replace(" ","").replace(":","").replace("-","");
    unsigned long long int d = fDate.toULongLong();
    d++;
    return QString::number(d);
}
void Conversation::getUpdate(QString token)
{
    QString url = "http://api.barafardayebehtar.ml:8080/";
    QString method = "getuserchats";
    if(chatType=="group")method = "getgroupchats";
    else if(chatType=="channel")method = "getchannelchats";
    QUrlQuery query;
    query.addQueryItem("token",token);
    query.addQueryItem("dst",_name);
    if(messageCount!=0)
    {
        query.addQueryItem("date",lastDate());
    }
    QJsonObject response = get(url + method,query);
    if(response.empty())
    {
        emit connection_lost();
    }
    else if(response.value("code").toString()=="401")
    {
        emit session_expired();
    }
    else if(response.value("code").toString()=="200")
    {
        QRegularExpression number("([0-9]+)");
        QRegularExpressionMatch match = number.match(response.value("message").toString());
        if(!match.hasMatch())
        {
            infoDialog* dialog = new infoDialog("Server Message: " + response.value("message").toString());
            dialog->exec();
        }
        int newMessageCount = match.captured(0).toInt();
        if(newMessageCount==0) { return; }
        for (int i = 0; i < newMessageCount; ++i)
        {
        QJsonObject message = response.value("block "+QString::number(i)).toObject();
        QString text,sender,date;
        text = message.value("body").toString();
        sender = message.value("src").toString();
        date = message.value("date").toString();
        Message* mes = new Message(messageCount,sender,text,date);
        messages.push_back(mes);
        emit newMessage_arrived(mes);
        messageCount++;
        if(mes->type()=="like")
        {
            QString id = mes->text().replace("#SERVERCOMMAND-LIKE","").replace("\n","");
            for(Message* m:messages)
            {
                if(m->id()==id.toInt())
                {
                    emit m->wasLiked();
                    return;
                }
            }
        }

        if(mes->type()=="delete")
        {
            QString id = mes->text().replace("#SERVERCOMMAND-DELETE","").replace("\n","");
            for(Message* m:messages)
            {
                if(m->id()==id.toInt())
                {
                    emit m->deleted();
                    return;
                }
            }
        }
        //user->writeToFile();
        }
    }
    else
    {
        emit getUpdate_failed();
    }

}
void Conversation::show_conversation()
{
    emit show(this);
}
const QString& Conversation::name() {return _name; }
const QString& Conversation::type() {return chatType; }
const vector<Message*>& Conversation::Messages() {return messages; }
Conversation::~Conversation()
{
    for(auto& x:messages)
    {
        delete x;
    }
    qDebug() << this->_name << "deleted";
}
QString Conversation::toString()
{
    QString res;
    res += chatType + "\n" + QString::number(messageCount) + "\n";
    res += _name + "\n";
    for(auto& message : messages)
    {
        res+=message->toString();
    }
    res+="MM:ENDOFCONV\n";
    return res;
}
