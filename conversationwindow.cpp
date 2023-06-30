#include "conversationwindow.h"
#include "ui_conversationwindow.h"
#include <QLabel>
#include <QScrollBar>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <functional>
extern User* user;
void ConversationWindow::addMessage(Message* message)
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
    label->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    layout->setGeometry(QRect(layout->geometry().x(),layout->geometry().y(),label->size().width(),label->size().height()));
    label->setFixedWidth(250);
    messagesLayout->addLayout(layout);
    connect(ui->scrollArea->verticalScrollBar(),&QScrollBar::rangeChanged,[&]()
            {
                QtConcurrent::run(bind(&ConversationWindow::scrollDown,this));
            });
}
ConversationWindow::ConversationWindow(Conversation* conversation,QWidget *parent) :
    QDialog(parent),
    conversation(conversation),
    ui(new Ui::ConversationWindow)
{
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    this->setWindowFlag(Qt::FramelessWindowHint);
    ui->setupUi(this);
    scrollingDown = false;
    this->setWindowTitle(conversation->name());
    ui->dstLabel->setText(conversation->name());
    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
    messagesLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setLayout(messagesLayout);
    messagesLayout->setAlignment(Qt::AlignBottom);
    connect(conversation,&Conversation::newMessage_arrived,this,&ConversationWindow::new_message);
    scrollAnim = new QPropertyAnimation(ui->scrollArea->verticalScrollBar(),"value");
    for(auto message: conversation->Messages())
    {
        addMessage(message);
    }
    ui->messageLineEdit->setText(conversation->draftMessage);
    //QtConcurrent::run(bind(&ConversationWindow::scrollDown,this));
}
ConversationWindow::~ConversationWindow()
{
    delete ui;
    delete scrollAnim;
    delete messagesLayout;
}
void ConversationWindow::new_message(Message* message)
{
    addMessage(message);
    //QtConcurrent::run(bind(&ConversationWindow::scrollDown,this));
}

void ConversationWindow::on_exitButton_clicked()
{
    this->close();
}
void ConversationWindow::scrollDown()
{

    QScrollBar* scrollbar = ui->scrollArea->verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum());
}
void ConversationWindow::on_minimizeButton_clicked()
{
    this->showMinimized();
}
void ConversationWindow::mousePressEvent(QMouseEvent* event)
{
    if(!isMouseOnToolbar(event->pos()))return;
    dragPosition = event->globalPos() - frameGeometry().topLeft();
    event->accept();
}
void ConversationWindow::mouseMoveEvent(QMouseEvent* event)
{
    if(!isMouseOnToolbar(event->pos()))return;
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}
bool ConversationWindow::isMouseOnToolbar(QPoint mousePos)
{
    QRect toolbar(0,0,350,25);
    return toolbar.contains(mousePos);
}

void ConversationWindow::on_messageLineEdit_textChanged(const QString &arg1)
{
    conversation->draftMessage = arg1;
}


void ConversationWindow::on_sendButton_clicked()
{
    if(ui->messageLineEdit->text()==""){return;}
    user->sendMessage(conversation->name(),conversation->type(),ui->messageLineEdit->text());
    ui->messageLineEdit->clear();
}


void ConversationWindow::on_scrollDownButton_clicked()
{
    scrollDown();
}

