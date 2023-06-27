#include "conversation.h"
#include <QRegularExpression>
#include "infodialog.h"
Conversation::Conversation(QString name,QString type,QObject *parent)
    : QObject{parent}
{
    _name = name;
    chatType = type;
    messageCount = 0;
}
QString Conversation::lastDate()
{
    QString date = messages[messageCount-1]->date();
    QString fDate =  date.replace(" ","").replace(":","").replace("-","");
    qDebug() << fDate;
    unsigned long long int d = fDate.toULongLong();
    d++;
    qDebug() << d;
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
        if(newMessageCount!=0)
        {
            for (int i = 0; i < newMessageCount; ++i)
            {
                QJsonObject message = response.value("block "+QString::number(i)).toObject();
                QString text,sender,date;
                text = message.value("body").toString();
                sender = message.value("src").toString();
                date = message.value("date").toString();
                Message* mes = new Message(messageCount,sender,text,date);
                messages.push_back(mes);
                qDebug() << sender << ":" << text;
                messageCount++;
                emit newMessage_arrived();
            }
        }
    }
}
void Conversation::show_conversation()
{
    qDebug() << "showing conversation";
}
const QString& Conversation::name() {return _name; }
const QString& Conversation::type() {return chatType; }
Conversation::~Conversation()
{
    for(auto& x:messages)
    {
        delete x;
    }
    qDebug() << this->_name << "deleted";
}
