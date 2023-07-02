#include "joinconversationwindow.h"
#include "ui_joinconversationwindow.h"
#include "user.h"
#include "infodialog.h"
extern User* user;
JoinConversationWindow::JoinConversationWindow(QString type,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoinConversationWindow)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    this->setWindowFlag(Qt::FramelessWindowHint);
    setup(type);
}
void JoinConversationWindow::setup(QString type)
{
    if(type=="channel")
    {
        ui->nameLineEdit->setPlaceholderText("Channel name...");
        connect(ui->joinButton,&QPushButton::clicked,this,&JoinConversationWindow::joinChannel);
        connect(user,&User::joinedConversation,[&](){
            infoDialog* dialog = new infoDialog("You have Successfully joined the channel\nIt is visibe in your Chat List now");
            dialog->exec();
            delete dialog;
            this->close();
        });
        connect(user,&User::alreadyInConversation,[&](){
            infoDialog* dialog = new infoDialog("You are already joined to this channel");
            dialog->exec();
            delete dialog;
        });
        connect(user,&User::conversationDoesntExist,[&](){
            infoDialog* dialog = new infoDialog("Conversation Does not exist\nMake sure you entered to name correctly");
            dialog->exec();
            delete dialog;
        });
    }
    else
    {
        ui->nameLineEdit->setPlaceholderText("Group name...");
        connect(ui->joinButton,&QPushButton::clicked,this,&JoinConversationWindow::joinGroup);
        connect(user,&User::joinedConversation,[&](){
            infoDialog* dialog = new infoDialog("You have Successfully joined the channel\nIt is visibe in your Chat List now");
            dialog->exec();
            delete dialog;
            user->sendMessage(ui->nameLineEdit->text(),"group","Hiii. I just joined this group");
            this->close();
        });
        connect(user,&User::alreadyInConversation,[&](){
            infoDialog* dialog = new infoDialog("You are already joined to this channel");
            dialog->exec();
            delete dialog;
        });
        connect(user,&User::conversationDoesntExist,[&](){
            infoDialog* dialog = new infoDialog("Conversation Does not exist\nMake sure you entered to name correctly");
            dialog->exec();
            delete dialog;
        });
    }
}
void JoinConversationWindow::joinChannel()
{
    if(ui->nameLineEdit->text()=="") { return;}
    user->joinConversation(ui->nameLineEdit->text(),"channel");
}
void JoinConversationWindow::joinGroup()
{
    if(ui->nameLineEdit->text()=="") { return;}
    user->joinConversation(ui->nameLineEdit->text(),"group");
}
JoinConversationWindow::~JoinConversationWindow()
{
    delete ui;
}

void JoinConversationWindow::on_exitButton_clicked()
{
    this->close();
}


void JoinConversationWindow::on_minimizeButton_clicked()
{
    this->showMinimized();
}


void JoinConversationWindow::on_cancelButton_clicked()
{
    this->close();
}

