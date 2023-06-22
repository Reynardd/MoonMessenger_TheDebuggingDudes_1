#ifndef USER_H
#define USER_H
#include "conversation.h"
#include <QObject>
#include <vector>
class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QString username,QString password,QString token,QObject *parent = nullptr);
    void logout();
    QString getToken();
    int* getConversationCount();
    const std::vector<Conversation*>& getConversations();
    void newConversation(QString name,QString type);
private:
    QString token;
    QString username;
    QString password;
    int userChatCount;
    int groupChatCount;
    int channelChatCount;
    std::vector<Conversation*> conversations;
private slots:


signals:
    void loggedOut();
};

#endif // USER_H
