#include "conversationwindow.h"
#include "ui_conversationwindow.h"
#include <QLabel>
ConversationWindow::ConversationWindow(Conversation* conversation,QWidget *parent) :
    QDialog(parent),
    conversation(conversation),
    ui(new Ui::ConversationWindow)
{
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    ui->setupUi(this);
    this->setWindowTitle(conversation->name());
    ui->dstLabel->setText(conversation->name());
    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
    messagesLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setLayout(messagesLayout);
    messagesLayout->setAlignment(Qt::AlignBottom);
    connect(conversation,&Conversation::newMessage_arrived,this,&ConversationWindow::new_message);
    for(auto message: conversation->Messages())
    {
        QLabel* label = new QLabel(" "+message->sender()+"\n    "+message->text(),this);
        QHBoxLayout* layout = new QHBoxLayout();
        if(message->sender()==conversation->name())
        {
            layout->setAlignment(Qt::AlignLeft);
            label->setStyleSheet("background-color:#0050FF;border-radius:15px;color:#000000");
        }
        else
        {
            layout->setAlignment(Qt::AlignRight);
            label->setStyleSheet("background-color:#00FFFF;border-radius:15px;color:#000000");
        }
        layout->addWidget(label);
        label->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Fixed);
        layout->setGeometry(QRect(layout->geometry().x(),layout->geometry().y(),label->size().width(),label->size().height()));
        //label->setAlignment(Qt::AlignVCenter);
        label->setFixedWidth(250);

        messagesLayout->addLayout(layout);
    }
}

ConversationWindow::~ConversationWindow()
{
    delete ui;
    delete messagesLayout;
    disconnect(conversation,&Conversation::newMessage_arrived,this,&ConversationWindow::new_message);
}
void ConversationWindow::new_message(Message* mes)
{

}

