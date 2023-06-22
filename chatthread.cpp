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
}
void ChatThread::stop()
{
    running = false;
}
void ChatThread::start()
{
    running = true;
    while(running)
    {
        QtConcurrent::run(bind(&ChatThread::check_new_user,this));
        QtConcurrent::run(bind(&ChatThread::check_new_channel,this));
        QtConcurrent::run(bind(&ChatThread::check_new_group,this));
        for(auto conv:user->getConversations())
        {
            QtConcurrent::run(&Conversation::getUpdate,conv,user->getToken());
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
        int n;
        if(type=="user")n=0;
        else if(type=="group")n=1;
        else n=2;
        int conversationCount = user->getConversationCount(type);
        if(conversationCount<newConversationCount)
        {
            for (int x = 0; x < newConversationCount-conversationCount; x++)
            {
                QJsonObject newConversation = response.value("block "+QString::number(x+conversationCount)).toObject();
                user->newConversation(newConversation.value("src").toString(),type);
            }
        }
    }
}
ChatThread::~ChatThread()
{
    stop();
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
