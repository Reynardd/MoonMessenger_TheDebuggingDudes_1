#include "user.h"
#include "request.h"
#include "infodialog.h"
#include <QFile>
#include <QTextStream>
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
    connect(conversation,&Conversation::newMessage_arrived,this,&User::new_change);
    conversations.push_back(conversation);
    if(type=="user")userChatCount++;
    else if(type=="gtoup")groupChatCount++;
    else {channelChatCount++;}

    emit new_conversation(conversation);
}
QString User::getUserName(){return username;}
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
        emit logOut_failed();
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
        emit logOut_failed();
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
User::~User()
{
    for(auto&x : conversations)
    {
        delete x;
    }
    qDebug() << "user deleted";
}
void User::writeToFile()
{
    QFile userFile("user.txt");
    if(!userFile.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        qDebug() << "couldn't open user file. ignoring";
        return;
    }
    QTextStream userStream(&userFile);
    userStream << username << "\n";
    userStream << password << "\n";
    userStream << token << "\n";
    userStream << userChatCount <<"\n" << groupChatCount << "\n" << channelChatCount<<"\n";
    for(auto& conversation : conversations)
    {
        QFile conversationFile(conversation->name());
        if(!conversationFile.open(QIODevice::ReadWrite | QIODevice::Truncate))
        {
            qDebug() << "couldn't open file. ignoring";
            continue;
        }
        userStream << conversation->name() << "\n";
        QTextStream conversationStream(&conversationFile);
        conversationStream << conversation->toString();
        conversationFile.close();
    }
    userFile.close();
}
void User::readFromFile()
{
    QFile userFile("user.txt");
    if(!userFile.open(QIODevice::ReadOnly | QIODevice::Text ))
    {
        infoDialog* info = new infoDialog("Couldn't read User data file\nPlease login again");
        info->exec();
        delete info;
        emit readFile_failed();
        return;
    }
    QTextStream stream(&userFile);
    username = stream.readLine();
    password = stream.readLine();
    token = stream.readLine();
    userChatCount = stream.readLine().toInt();
    groupChatCount = stream.readLine().toInt();
    channelChatCount = stream.readLine().toInt();
    QString conversationName;
    while(!stream.atEnd())
    {
        conversationName = stream.readLine();
        QFile conversationFile(conversationName);
        if(!conversationFile.open(QIODevice::ReadWrite))
        {
            qDebug() << "failed to open conv file";
            continue;
        }
        QTextStream conversationStream(&conversationFile);
        QString data = conversationStream.readAll();
        Conversation* conversationPtr = new Conversation(data,this);
        connect(conversationPtr,&Conversation::newMessage_arrived,this,&User::new_change);
        conversations.push_back(conversationPtr);
        emit new_conversation(conversationPtr);
    }
}
void User::new_change()
{
    this->writeToFile();
}
void User::sessionExpiredSlot()
{

}
