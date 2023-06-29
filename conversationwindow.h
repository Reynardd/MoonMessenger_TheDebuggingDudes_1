#ifndef CONVERSATIONWINDOW_H
#define CONVERSATIONWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include "conversation.h"
#include <QMouseEvent>
#include "user.h"
namespace Ui {
class ConversationWindow;
}

class ConversationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConversationWindow(Conversation* conversation,QWidget *parent = nullptr);
    ~ConversationWindow();
private slots:
    void new_message(Message* mes);

    void on_exitButton_clicked();

    void on_minimizeButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    QVBoxLayout* messagesLayout;
    Conversation* conversation;
    Ui::ConversationWindow *ui;
    void addMessage(Message* message);
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    bool isMouseOnToolbar(QPoint mousePos);
    void scrollDown();
    int sliderPos;
    QPoint dragPosition;
signals:
    void sendMessage(QString data);
};




#endif // CONVERSATIONWINDOW_H
