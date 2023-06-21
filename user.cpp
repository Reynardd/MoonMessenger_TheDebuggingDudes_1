#include "user.h"
#include "request.h"
#include "infodialog.h"
User::User(QString _username,QString _password,QString _token,QObject *parent)
    : QObject{parent}
{
    username = _username;
    password = _password;
    token = _token;
}
void User:: newConversation(QString name,QString type)
{

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
}
