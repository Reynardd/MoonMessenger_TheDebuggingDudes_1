#ifndef CHATLISTPAGE_H
#define CHATLISTPAGE_H
#include <QPropertyAnimation>
#include <QWidget>
#include "user.h"
#include "chatthread.h"
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
    void new_conversation(QString name,QString type);

private:
    Ui::ChatListPage *ui;
    QPropertyAnimation* menuAnimation;
    QPropertyAnimation* menuButtonAnimation;
    QVBoxLayout* chatsLayout;
    User* user;
    ChatThread* chatThread ;
    bool showingMenu;
};

#endif // CHATLISTPAGE_H
