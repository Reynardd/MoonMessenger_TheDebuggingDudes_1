#include "chatbutton.h"
ChatButton::ChatButton(Conversation* conversation,QWidget* parent) : QPushButton(parent)
{
    this->setText("                  " + conversation->name());
    connect(this,&QPushButton::clicked,conversation,&Conversation::show_conversation);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    this->setFixedHeight(50);
    this->setStyleSheet("QPushButton{image:url(:/label/"+conversation->type()+"ChatButton.svg);color:white;border:none;text-align:left}\
                         QPushButton:hover{image:url(:/label/"+conversation->type()+"ChatButtonHover.svg);}\
                         QPushButton:pressed{image:url(:/label/"+conversation->type()+"ChatButtonPressed.svg);}");
    spacerItem = new QWidget(parent);
    spacerItem->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    spacerItem->setFixedHeight(2);
    spacerItem->setStyleSheet("image:url(:/label/line.svg)");

}
