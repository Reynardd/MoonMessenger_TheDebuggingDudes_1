#include "chatlistpage.h"
#include "ui_chatlistpage.h"

ChatListPage::ChatListPage(QString username,QString password,QString token,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatListPage)
{
    ui->setupUi(this);
    this->setStyleSheet("#centralwidget{background-image: url(:/back/background.jpg);}");
    user = new User(username,password,token,this);
    this->setWindowTitle(username);
}

ChatListPage::~ChatListPage()
{
    delete ui;
}
