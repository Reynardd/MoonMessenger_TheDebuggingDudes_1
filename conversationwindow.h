#ifndef CONVERSATIONWINDOW_H
#define CONVERSATIONWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include "conversation.h"
#include <QMouseEvent>
#include <QPropertyAnimation>
#include "user.h"
#include <QTimer>
namespace Ui {
class ConversationWindow;
}

class ConversationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConversationWindow(Conversation* conversation,QWidget *parent = nullptr);
    ~ConversationWindow();
    QString conversationName;
private slots:
    void new_message(Message* mes);
    void on_messageLineEdit_textChanged(const QString &arg1);
    void on_sendButton_clicked();
    void on_scrollDownButton_clicked();
    void on_exitButton_3_clicked();
    void on_minimizeButton_3_clicked();
    void scrollbarValueChanged(int);

private:
    QVBoxLayout* messagesLayout;
    Conversation* conversation;
    Ui::ConversationWindow *ui;
    void addMessage(Message* message);
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    bool isMouseOnToolbar(QPoint mousePos);
    void animationScrollDown();
    bool animationOnRun;
    QTimer buttonHandler;
    void handleButton(bool showing);
    QPropertyAnimation* scrollButtonAnim;
    bool buttonAnimOnRun;
    void scrollDown();
    QPropertyAnimation* scrollAnim;
    QPoint dragPosition;
signals:
    void sendMessage(QString data);
};




#endif // CONVERSATIONWINDOW_H
