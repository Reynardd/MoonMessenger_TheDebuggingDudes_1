#ifndef CHATLISTPAGE_H
#define CHATLISTPAGE_H
#include <QPropertyAnimation>
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

private slots:
    void on_menuToggleButton_clicked();
    void userLoggedOut();

private:
    Ui::ChatListPage *ui;
    QPropertyAnimation* menuAnimation;
    QPropertyAnimation* menuButtonAnimation;
    User* user;
    bool showingMenu;
};

#endif // CHATLISTPAGE_H
