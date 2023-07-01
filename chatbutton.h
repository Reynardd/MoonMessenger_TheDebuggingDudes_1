#ifndef CHATBUTTON_H
#define CHATBUTTON_H

#include <QPushButton>
#include <QObject>
#include "conversation.h"
class ChatButton : public QPushButton
{
public:
    ChatButton(Conversation* conversation,QWidget* parent = nullptr);
    QWidget* spacerItem;
};

#endif // CHATBUTTON_H
