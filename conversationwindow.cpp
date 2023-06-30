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
    sliderPos = 0;
    this->setWindowTitle(conversation->name());
    ui->dstLabel->setText(conversation->name());
    ui->scrollArea->setWidget(ui->scrollAreaWidgetContents);
    messagesLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setLayout(messagesLayout);
    messagesLayout->setAlignment(Qt::AlignBottom);
    connect(conversation,&Conversation::newMessage_arrived,this,&ConversationWindow::new_message);
    for(auto message: conversation->Messages())
    {
        addMessage(message);
    }
    ui->lineEdit->setEnabled(true);
    QtConcurrent::run(bind(&ConversationWindow::scrollDown,this));
}
ConversationWindow::~ConversationWindow()
{
    delete ui;
    delete messagesLayout;
}
void ConversationWindow::new_message(Message* message)
{
    addMessage(message);
    QtConcurrent::run(bind(&ConversationWindow::scrollDown,this));
}

void ConversationWindow::on_exitButton_clicked()
{
    this->close();
}
void ConversationWindow::scrollDown()
{
    QEventLoop eventLoop;
    QTimer timeoutTimer;
    timeoutTimer.setSingleShot(true);
    QObject::connect(&timeoutTimer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);
    timeoutTimer.start(100);
    eventLoop.exec();
    int lastVal = ui->scrollArea->verticalScrollBar()->value();
    while(true)
    {
        ui->scrollArea->verticalScrollBar()->setValue(lastVal+5);
        if(lastVal==ui->scrollArea->verticalScrollBar()->value()){break;}
        lastVal=ui->scrollArea->verticalScrollBar()->value();
    }
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

void ConversationWindow::on_pushButton_clicked()
{
    if(ui->lineEdit->text()==""){return;}
    user->sendMessage(conversation->name(),conversation->type(),ui->lineEdit->text());
    ui->lineEdit->clear();
}


void ConversationWindow::on_pushButton_2_clicked()
{
    scrollDown();
}

