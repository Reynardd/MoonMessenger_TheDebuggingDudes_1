#ifndef CONVERSATIONWINDOW_H
#define CONVERSATIONWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include "conversation.h"
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

private:
    QVBoxLayout* messagesLayout;
    Conversation* conversation;
    Ui::ConversationWindow *ui;
signals:
    void sendMessage(QString data);
};




#endif // CONVERSATIONWINDOW_H
