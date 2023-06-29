#ifndef CHATLISTPAGE_H
#define CHATLISTPAGE_H
#include <QPropertyAnimation>
#include <QWidget>
#include "user.h"
#include "conversationwindow.h"
#include "chatthread.h"
#include <QMouseEvent>
namespace Ui {
class ChatListPage;
}

class ChatListPage : public QWidget
{
    Q_OBJECT

public:
    explicit ChatListPage(QString username,QString password,QString token,bool readFromFile = false,QWidget *parent = nullptr);
    ~ChatListPage();

private slots:
    void on_menuToggleButton_clicked();
    void userLoggedOut();
    void new_conversation(Conversation* conversation);

    void on_pushButton_clicked();

    void on_exitButton_clicked();
    void showConversation(Conversation* conv);
    void on_minimizeButton_clicked();

private:
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    bool isMouseOnToolbar(QPoint mousePos);
    QPoint dragPosition;
    Ui::ChatListPage *ui;
    QPropertyAnimation* menuAnimation;
    QPropertyAnimation* menuButtonAnimation;
    QVBoxLayout* chatsLayout;
    //User* user;
    ChatThread* chatThread ;
    bool showingMenu;
};

#endif // CHATLISTPAGE_H
