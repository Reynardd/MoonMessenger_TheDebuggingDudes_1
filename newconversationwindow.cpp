#include "newconversationwindow.h"
#include "ui_newconversationwindow.h"
#include "user.h"
#include "infodialog.h"
extern User* user;
NewConversationWindow::NewConversationWindow(QString type,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewConversationWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    this->setWindowFlag(Qt::FramelessWindowHint);
}
void NewConversationWindow::userSetup()
{
    ui->nameLineEdit->setPlaceholderText("Username");
    ui->lineEdit->setPlaceholderText("Write a message...");
    connect(user,&User::convesationDoesntExist,[](){
        infoDialog* dialog = new infoDialog("User not found\nTry another username");
        dialog->exec();
        delete dialog;
    });
    connect(user,&User::messageSentSuccessfully,[&](){
        infoDialog* dialog = new infoDialog("Message was sent to the user\nYou should be able to see them in chats now");
        dialog->exec();
        delete dialog;
        close();
    });
}
void NewConversationWindow::channelSetup()
{
    ui->nameLineEdit->setPlaceholderText("Channel Name");
    ui->lineEdit->setPlaceholderText("Channel Title");
}
void NewConversationWindow::groupSetup()
{
    ui->nameLineEdit->setPlaceholderText("Group Name");
    ui->lineEdit->setPlaceholderText("Group Title");
}
NewConversationWindow::~NewConversationWindow()
{
    delete ui;
}
void NewConversationWindow::mousePressEvent(QMouseEvent* event)
{
    if(!isMouseOnToolbar(event->pos()))return;
    dragPosition = event->globalPos() - frameGeometry().topLeft();
    event->accept();
}
void NewConversationWindow::mouseMoveEvent(QMouseEvent* event)
{
    if(!isMouseOnToolbar(event->pos()))return;
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}
bool NewConversationWindow::isMouseOnToolbar(QPoint mousePos)
{
    QRect toolbar(0,0,350,30);
    return toolbar.contains(mousePos);
}
