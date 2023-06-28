#include "chatthread.h"
#include <QtConcurrent/QtConcurrent>
#include "yesnodialog.h"
#include "infodialog.h"
#include "request.h"
#include <QThread>
#define URL QString::fromUtf8("http://api.barafardayebehtar.ml:8080/")


ChatThread::ChatThread(User* user,QObject *parent)
    : QObject{parent}
{
    this->user= user;
    running = false;
    layout = nullptr;
}
void ChatThread::setLayout(QLayout* layout)
{
    this->layout = layout;
}
void ChatThread::stop()
{
    qDebug() <<"stopping chatThread";
    threadPool.waitForDone();
    running = false;
    qDebug() << "chatThread stopped";
}
void ChatThread::start()
{
    running = true;
    while(running)
    {
        QtConcurrent::run(&threadPool,bind(&ChatThread::check_new_user,this));
        QtConcurrent::run(&threadPool,bind(&ChatThread::check_new_channel,this));
        QtConcurrent::run(&threadPool,bind(&ChatThread::check_new_group,this));
        for(auto conv:user->getConversations())
        {
            QtConcurrent::run(&threadPool,&Conversation::getUpdate,conv,user->getToken());
        }
        QThread::sleep(1);
    }
}
void ChatThread::check_new(QString type)
{
    QUrlQuery query;
    query.addQueryItem("token",user->getToken());
    QJsonObject response = get(URL+"get"+type+"list",query);
    if(response.empty())
    {
        connectionLost();
        return;
    }
    else if(response.value("code").toString()=="401")
    {
        emit sessionExpired();
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
        int newConversationCount = match.captured(0).toInt();
        int conversationCount = user->getConversationCount(type);
        if(conversationCount<newConversationCount)
        {
            for (int x = 0; x < newConversationCount-conversationCount; x++)
            {
                QJsonObject newConversation = response.value("block "+QString::number(x+conversationCount)).toObject();
                QString senderKey = "src";
                if(type=="channel")senderKey = "channel_name";
                if(type=="group")senderKey = "group_name";
                user->newConversation(newConversation.value(senderKey).toString(),type);
            }
        }
    }
}
ChatThread::~ChatThread()
{
    stop();
    qDebug() << "chatthread deleted";
}
void ChatThread::check_new_user()
{
    check_new("user");
}
void ChatThread::check_new_group()
{
    check_new("group");
}
void ChatThread::check_new_channel()
{
    check_new("channel");
}
void ChatThread::connectionLost()
{
    running = false;
    YesNoDialog * dialog = new YesNoDialog("It Seems Like we have lost Connection to the server.\nDo you want to switch to Offline Mode?");
    if(dialog->exec()==QDialog::Rejected)
    {
        running = true;
    }
}
