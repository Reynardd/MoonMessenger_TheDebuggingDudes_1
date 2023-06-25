#include "user.h"
#include "request.h"
#include "infodialog.h"
User::User(QString _username,QString _password,QString _token,QObject *parent)
    : QObject{parent}
{
    username = _username;
    password = _password;
    token = _token;
    userChatCount = 0;
    groupChatCount = 0;
    channelChatCount = 0;
}
void User:: newConversation(QString name,QString type)
{
    Conversation* conversation = new Conversation(name,type);
    conversations.push_back(conversation);
    if(type=="user")userChatCount++;
    else if(type=="gtoup")groupChatCount++;
    else channelChatCount++;

    emit new_conversation(name,type);
}
int User::getConversationCount(QString type)
{
    if(type=="user")return userChatCount;
    if(type=="group")return groupChatCount;
    if(type=="channel")return channelChatCount;
    return 0;
}
void User::logout()
{
    QUrlQuery query;
    query.addQueryItem("username",username);
    query.addQueryItem("password",password);
    QJsonObject response = get("http://api.barafardayebehtar.ml:8080/logout",query);
    if(response.empty())
    {
        infoDialog *dialog = new infoDialog("Couldn't Connect to the Host!\nCheck your Internet Connection");
        dialog->exec();
        return;
    }
    if(response.value("code").toString()=="200")
    {
        infoDialog *dialog = new infoDialog("Logged Out Succesfully");
        dialog->exec();
        emit loggedOut();
        return;
    }
    else
    {
        infoDialog *dialog = new infoDialog("Something went Wrong\nServer Message: "+response.value("message").toString());
        dialog->exec();
        return;
    }
}
const std::vector<Conversation*>& User::getConversations()
{
    return conversations;
}
QString User::getToken()
{
    return token;
}
