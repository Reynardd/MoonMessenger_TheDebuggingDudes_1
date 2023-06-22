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
    connect(menuAnimation,&QPropertyAnimation::finished,[&](){ui->menuToggleButton->setEnabled(true);});
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
    ui->menuToggleButton->setEnabled(false);
    if(showingMenu)
    {
        menuAnimation->setStartValue(ui->menuLayout->geometry());

        menuAnimation->setEndValue(QRect(ui->menuLayout->geometry().x()-230,ui->menuLayout->geometry().y(),\
        ui->menuLayout->width(),ui->menuLayout->height()));


        menuButtonAnimation->setStartValue(ui->menuToggleButton->geometry());

        menuButtonAnimation->setEndValue(QRect(ui->menuToggleButton->geometry().x()-230,ui->menuToggleButton->geometry().y()\
        ,ui->menuToggleButton->width(),ui->menuToggleButton->height()));

        menuAnimation->setDuration(170);
        menuButtonAnimation->setDuration(170);
        menuAnimation->start();
        menuButtonAnimation->start();
        showingMenu = false;
        ui->menuToggleButton->setStyleSheet(\
        "QPushButton {\
        image: url(:/back/arrow.svg);\
        border:none\
        }\
        QPushButton:hover {\
        image: url(:/back/arrowHover.svg);\
        }\
        QPushButton:pressed {\
        image: url(:/back/arrowPressed.svg);\
        }");
    }
    else
    {
        menuAnimation->setStartValue(ui->menuLayout->geometry());

        menuAnimation->setEndValue(QRect(ui->menuLayout->geometry().x()+230,ui->menuLayout->geometry().y(),\
        ui->menuLayout->width(),ui->menuLayout->height()));


        menuButtonAnimation->setStartValue(ui->menuToggleButton->geometry());

        menuButtonAnimation->setEndValue(QRect(ui->menuToggleButton->geometry().x()+230,ui->menuToggleButton->geometry().y()\
        ,ui->menuToggleButton->width(),ui->menuToggleButton->height()));

        menuAnimation->setDuration(170);
        menuButtonAnimation->setDuration(170);
        menuAnimation->start();
        menuButtonAnimation->start();
        showingMenu = true;
        ui->menuToggleButton->setStyleSheet(\
        "QPushButton {\
        image: url(:/back/arrowBack.svg);\
        border:none\
        }\
        QPushButton:hover {\
        image: url(:/back/arrowBackHover.svg);\
        }\
        QPushButton:pressed {\
        image: url(:/back/arrowBackPressed.svg);\
        }");
    }
}

