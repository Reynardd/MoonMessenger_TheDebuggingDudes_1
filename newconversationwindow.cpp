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
    setup(type);
}
void NewConversationWindow::setup(QString type)
{
    if(type=="user") {userSetup(); }
    else if(type=="channel") { channelSetup(); }
    else { groupSetup(); }
}
void NewConversationWindow::userSetup()
{
    ui->nameLineEdit->setPlaceholderText("Username");
    ui->lineEdit->setPlaceholderText("Write a message...");
    ui->createButton->setStyleSheet("QPushButton{image: url(:/label/sendButtonText.svg);border:none;}\
                                     QPushButton:hover {image: url(:/label/sendButtonTextHover.svg);border:none;}\
                                     QPushButton:pressed {image: url(:/label/sendButtonTextPressed.svg);border:none;}");

    connect(user,&User::conversationDoesntExist,[](){
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
    connect(ui->createButton,&QPushButton::clicked,this,&NewConversationWindow::textUser);
}
void NewConversationWindow::channelSetup()
{
    ui->nameLineEdit->setPlaceholderText("Channel Name");
    ui->lineEdit->setPlaceholderText("Channel Title");
    connect(ui->createButton,&QPushButton::clicked,this,&NewConversationWindow::createChannel);
    connect(user,&User::conversationAlreadyExist,[](){
        infoDialog* dialog = new infoDialog("A Channel with this username already exist\nTry another name");
        dialog->exec();
        delete dialog;
    });
    connect(user,&User::conversationCreated,[&](){
        infoDialog* dialog = new infoDialog("Channel was created successfully\nYou should be able to see it in chats");
        dialog->exec();
        delete dialog;
        close();
    });
}
void NewConversationWindow::groupSetup()
{
    ui->nameLineEdit->setPlaceholderText("Group Name");
    ui->lineEdit->setPlaceholderText("Group Title");
    connect(ui->createButton,&QPushButton::clicked,this,&NewConversationWindow::createGroup);
    connect(user,&User::conversationAlreadyExist,[](){
        infoDialog* dialog = new infoDialog("A Group with this username already exist\nTry another name");
        dialog->exec();
        delete dialog;
    });
    connect(user,&User::conversationCreated,[&](){
        infoDialog* dialog = new infoDialog("Group was created successfully\nYou should be able to see it in chats");
        dialog->exec();
        delete dialog;
        close();
    });
}
void NewConversationWindow::textUser()
{
    user->sendMessage(ui->nameLineEdit->text(),"user",ui->lineEdit->text());
}
void NewConversationWindow::createChannel()
{
    user->createConversation(ui->nameLineEdit->text(),ui->lineEdit->text(),"channel");
}
void NewConversationWindow::createGroup()
{
    user->createConversation(ui->nameLineEdit->text(),ui->lineEdit->text(),"group");
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

void NewConversationWindow::on_exitButton_clicked()
{
    this->close();
}


void NewConversationWindow::on_minimizeButton_clicked()
{
    this->showMinimized();
}


void NewConversationWindow::on_cancelButton_clicked()
{
    this->close();
}

