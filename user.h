#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr);
    void logout();
private:
    QString token;
    QString username;
    QString Password;


signals:

};

#endif // USER_H
