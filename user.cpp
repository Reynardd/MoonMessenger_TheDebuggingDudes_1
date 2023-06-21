#include "user.h"

User::User(QString username,QString password,QString token,QObject *parent)
    : QObject{parent}
{
    username = username;
    password = password;
    token = token;
}
