
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
    ~User();
    void logout();
    QString getUserName();
    QString getToken();
    int getConversationCount(QString type);
    const std::vector<Conversation*>& getConversations();
    void newConversation(QString name,QString type);
    void readFromFile();
    void writeToFile();
    void sendMessage(QString conversationName,QString conversationType,QString data);
    void createConversation(QString name,QString title,QString type);
    void joinConversation(QString name,QString type);
private:
    QString token;
    QString username;
    QString password;
    int userChatCount;
    int groupChatCount;
    int channelChatCount;
    std::vector<Conversation*> conversations;
private slots:
    void sessionExpiredSlot();
    void new_change(Message*);

signals:
    void loggedOut();
    void logOut_failed();
    void sendMessage_faild();
    void readFile_failed();
    void sessionExpiredSignal();
    void new_conversation(Conversation* conversation);
    void conversationCreated();
    void conversationAlreadyExist();
    void conversationDoesntExist();
    void joinedConversation();
    void alreadyInConversation();
    void messageSentSuccessfully();

};
#endif // USER_H
