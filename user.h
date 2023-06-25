
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
    int getConversationCount(QString type);
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
    void new_conversation(QString name,QString type);
};

#endif // USER_H
