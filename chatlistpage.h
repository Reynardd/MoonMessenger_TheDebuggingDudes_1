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
    void userLoggedOut();
    void connectionLost();
    void sessionExpired();
    void new_conversation(Conversation* conversation);
    void on_pushButton_clicked();
    void on_exitButton_clicked();
    void showConversation(Conversation* conv);
    void on_minimizeButton_clicked();
    void on_menuToggleButton_clicked(bool checked);
    void on_pushButton_2_clicked();
    void on_switchMode_toggled(bool checked);

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    bool showingDialogFlag;
    bool logOutFlag;
    bool sessionExpiredFlag;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    bool isMouseOnToolbar(QPoint mousePos);
    ConversationWindow * currentChatWindow;
    QPoint dragPosition;
    Ui::ChatListPage *ui;
    QPropertyAnimation* menuAnimation;
    QPropertyAnimation* menuButtonAnimation;
    QPropertyAnimation* switchAnimation;
    QVBoxLayout* chatsLayout;

    //User* user;
    ChatThread* chatThread ;
    bool showingMenu;
};

#endif // CHATLISTPAGE_H
