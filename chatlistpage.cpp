#include "chatlistpage.h"
#include "ui_chatlistpage.h"
#include "mainwindow.h"
ChatListPage::ChatListPage(QString username,QString password,QString token,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatListPage)
{
    ui->setupUi(this);
    showingMenu = false;
    this->setStyleSheet("#centralwidget{background-image: url(:/back/background.jpg);}");
    user = new User(username,password,token,this);
    this->setWindowTitle(username);
    ui->nameLabel->setText("Logged in as "+ username);
    connect(ui->pushButton,&QPushButton::clicked,user,&User::logout);
    connect(user,&User::loggedOut,this,&ChatListPage::userLoggedOut);
    menuAnimation = new QPropertyAnimation(ui->menuLayout,"geometry",this);
    menuButtonAnimation = new QPropertyAnimation(ui->menuToggleButton,"geometry",this);
}

ChatListPage::~ChatListPage()
{
    delete ui;
}
void ChatListPage::userLoggedOut()
{
    MainWindow * loginPage = new MainWindow();
    loginPage->show();
    this->close();
}
void ChatListPage::on_menuToggleButton_clicked()
{
    if(showingMenu)
    {
        //add animation later
        ui->menuToggleButton->setGeometry(ui->menuToggleButton->geometry().x() - 230,ui->menuToggleButton->geometry().y(),\
        ui->menuToggleButton->geometry().width(),ui->menuToggleButton->geometry().height());
        ui->menuLayout->setGeometry(ui->menuLayout->geometry().x() - 230,ui->menuLayout->geometry().y(),\
        ui->menuLayout->geometry().width(),ui->menuLayout->geometry().height());
        showingMenu = false;
        ui->menuToggleButton->setText(">");
    }
    else
    {
        ui->menuToggleButton->setGeometry(ui->menuToggleButton->geometry().x() + 230,ui->menuToggleButton->geometry().y(),\
        ui->menuToggleButton->geometry().width(),ui->menuToggleButton->geometry().height());
        ui->menuLayout->setGeometry(ui->menuLayout->geometry().x() + 230,ui->menuLayout->geometry().y(),\
        ui->menuLayout->geometry().width(),ui->menuLayout->geometry().height());
        showingMenu = true;
        ui->menuToggleButton->setText("<");
    }
}

