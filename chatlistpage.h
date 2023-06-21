#ifndef CHATLISTPAGE_H
#define CHATLISTPAGE_H

#include <QWidget>
#include "user.h"
namespace Ui {
class ChatListPage;
}

class ChatListPage : public QWidget
{
    Q_OBJECT

public:
    explicit ChatListPage(QString username,QString password,QString token,QWidget *parent = nullptr);
    ~ChatListPage();

private:
    Ui::ChatListPage *ui;
    User* user;
};

#endif // CHATLISTPAGE_H
