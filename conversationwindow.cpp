#include "conversationwindow.h"
#include "ui_conversationwindow.h"
#include <QLabel>
#include <QScrollBar>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QThread>
#include <QtConcurrent/QtConcurrent>
#include <functional>
#include "messagerect.h"
extern User* user;
void ConversationWindow::addMessage(Message* message)
{
    bool fromMe = false;
    QHBoxLayout* layout = new QHBoxLayout();
    layout->setAlignment(Qt::AlignLeft);
    if(message->sender()==user->getUserName())
    {
        fromMe=true;
        layout->setAlignment(Qt::AlignRight);
    }
    MessageRect* label = new MessageRect(message,fromMe,this);

    layout->addWidget(label);
    messagesLayout->addLayout(layout);

}
ConversationWindow::ConversationWindow(Conversation* conversation,QWidget *parent) :
    QDialog(parent),
    conversation(conversation),
    ui(new Ui::ConversationWindow)
{
    animationOnRun = false;
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    this->setWindowFlag(Qt::FramelessWindowHint);
    ui->setupUi(this);
    this->setWindowTitle(conversation->name());
    ui->dstLabel->setText(conversation->name());
    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
    messagesLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setLayout(messagesLayout);
    messagesLayout->setAlignment(Qt::AlignBottom);
    connect(conversation,&Conversation::newMessage_arrived,this,&ConversationWindow::new_message);
    conversationName = conversation->name();
    connect(&buttonHandler,&QTimer::timeout,[&](){handleButton(false);});

    scrollAnim = new QPropertyAnimation(ui->scrollArea->verticalScrollBar(),"value");
    connect(scrollAnim,&QPropertyAnimation::finished,[&](){animationOnRun=false;});

    for(auto message: conversation->Messages()) { addMessage(message); }
    connect(ui->scrollArea->verticalScrollBar(),&QScrollBar::rangeChanged,this,&ConversationWindow::animationScrollDown);

    scrollButtonAnim = new QPropertyAnimation(ui->scrollDownButton,"geometry");
    buttonAnimOnRun = false;
    buttonHandler.setSingleShot(true);
    connect(scrollButtonAnim,&QPropertyAnimation::finished,[&](){buttonAnimOnRun = false;});




    ui->messageLineEdit->setText(conversation->draftMessage);
    ui->scrollDownButton->raise();

    QTimer*waiter = new QTimer;
    waiter->setSingleShot(true);
    connect(waiter,&QTimer::timeout,[&](){
        connect(ui->scrollArea->verticalScrollBar(),SIGNAL(valueChanged(int)),this,SLOT(scrollbarValueChanged(int)));

    });
    waiter->start(1000);
}
ConversationWindow::~ConversationWindow()
{
    delete ui;
    delete scrollAnim;
    delete scrollButtonAnim;
    delete messagesLayout;
}
void ConversationWindow::new_message(Message* message)
{
    addMessage(message);
}

void ConversationWindow::scrollDown()
{
    QScrollBar* scrollbar = ui->scrollArea->verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum());
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

void ConversationWindow::animationScrollDown()
{
    if(!animationOnRun)
    {
        animationOnRun=true;
        scrollAnim->setStartValue(ui->scrollArea->verticalScrollBar()->value());
        scrollAnim->setEndValue(ui->scrollArea->verticalScrollBar()->maximum());
        scrollAnim->setDuration(100);
        scrollAnim->start();
    }
}

void ConversationWindow::handleButton(bool showing)
{
    QRect showPos(29,390,ui->scrollDownButton->width(),ui->scrollDownButton->height());
    QRect hidePos(29,590,ui->scrollDownButton->width(),ui->scrollDownButton->height());
    if(showing)
    {
        buttonHandler.stop();
        buttonHandler.start(2000);
        if(ui->scrollDownButton->geometry()==showPos) {return;}
        scrollButtonAnim->setStartValue(hidePos);;
        scrollButtonAnim->setEndValue(showPos);
        scrollButtonAnim->setDuration(100);
        if(buttonAnimOnRun){return;}
        buttonAnimOnRun = true;
        scrollButtonAnim->start();
    }
    else
    {
        if(buttonAnimOnRun){return;}
        if(ui->scrollDownButton->geometry()==hidePos) {return;}
        scrollButtonAnim->stop();
        buttonHandler.stop();
        scrollButtonAnim->setStartValue(showPos);
        scrollButtonAnim->setEndValue(hidePos);
        scrollButtonAnim->setDuration(100);
        buttonAnimOnRun = true;
        scrollButtonAnim->start();
    }
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
    animationScrollDown();
}


void ConversationWindow::on_exitButton_3_clicked()
{
    this->close();
}


void ConversationWindow::on_minimizeButton_3_clicked()
{
    this->showMinimized();
}

void ConversationWindow::scrollbarValueChanged(int value)
{
    if(value==ui->scrollArea->verticalScrollBar()->maximum())
    {
        handleButton(false);
        return;
    }
    else
    { handleButton(true); }
}

