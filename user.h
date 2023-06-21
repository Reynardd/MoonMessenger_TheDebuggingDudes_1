#ifndef USER_H
#define USER_H
#include "conversation.h"
#include <QObject>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QString username,QString password,QString token,QObject *parent = nullptr);
    void logout();
private:
    QString token;
    QString username;
    QString password;
    QVector<Conversation> conversations;
private slots:
    void newConversation(QString name,QString type);

signals:

};

#endif // USER_H
