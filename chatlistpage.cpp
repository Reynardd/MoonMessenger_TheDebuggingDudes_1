#include "chatlistpage.h"
#include "ui_chatlistpage.h"

ChatListPage::ChatListPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatListPage)
{
    ui->setupUi(this);
    this->setStyleSheet("#centralwidget{background-image: url(:/back/background.jpg);}");
}

ChatListPage::~ChatListPage()
{
    delete ui;
}
