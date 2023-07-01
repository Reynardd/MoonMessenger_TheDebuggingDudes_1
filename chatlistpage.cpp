#include "chatlistpage.h"
#include "ui_chatlistpage.h"
#include "mainwindow.h"
#include <QFile>
#include "user.h"
#include <QtConcurrent/QtConcurrent>
#include <QVBoxLayout>
#include <QDebug>
#include "yesnodialog.h"
#include "infodialog.h"
#include "newconversationwindow.h"
extern User* user;
ChatListPage::ChatListPage(QString username,QString password,QString token,bool readFromFile,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatListPage)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    this->setWindowFlag(Qt::FramelessWindowHint);
    showingDialogFlag = false;
    showingMenu = false;
    currentChatWindow = nullptr;
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    this->setStyleSheet("#centralwidget{background-image: url(:/back/background.jpg);}");
    user = new User(username,password,token,this);
    chatsLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    connect(user,&User::loggedOut,this,&ChatListPage::userLoggedOut);
    connect(user,SIGNAL(new_conversation(Conversation*)),this,SLOT(new_conversation(Conversation*)));
    if(readFromFile)user->readFromFile();
    chatThread = new ChatThread(user,this);
    connect(chatThread,&ChatThread::connectionLost,this,&ChatListPage::connectionLost);
    connect(chatThread,&ChatThread::sessionExpired,this,&ChatListPage::sessionExpired);
    connect(chatThread,SIGNAL(isStopped(bool)),ui->switchMode,SLOT(setChecked(bool)));
    this->setWindowTitle(user->getUserName());
    ui->nameLabel->setText("Logged in as "+ user->getUserName());
    ui->scrollAreaWidgetContents->setLayout(chatsLayout);
    ui->scrollArea->setWidgetResizable(true);
    chatsLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->circle->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    connect(user,&User::logOut_failed,[&](){if(logOutFlag)
    {
//    QtConcurrent::run(&ChatThread::start,chatThread);
    chatThread->start();
    }});

    menuAnimation = new QPropertyAnimation(ui->menuLayout,"geometry",this);
    menuButtonAnimation = new QPropertyAnimation(ui->menuToggleButton,"geometry",this);
    switchAnimation = new QPropertyAnimation(ui->circle,"geometry",this);
    connect(menuAnimation,&QPropertyAnimation::finished,[&](){ui->menuToggleButton->setEnabled(true);});    //chatThread->start();
//    QtConcurrent::run(&ChatThread::start,chatThread);
    chatThread->start();
}

ChatListPage::~ChatListPage()
{
    chatThread->stop();
    delete chatThread;
    delete chatsLayout;
    delete user;
    delete menuAnimation;
    delete menuButtonAnimation;
    delete ui;
    qDebug() << "chatlistpage deleted";
}
void ChatListPage::connectionLost()
{
    if(showingDialogFlag)return;
    showingDialogFlag = true;
    YesNoDialog* dialog = new YesNoDialog("It seems we've lost connection to the server\nDo you want to switch to offline mode?",this);
    if(dialog->exec()==QDialog::Rejected)
    {
        chatThread->start();
    }
    showingDialogFlag = false;
}

void ChatListPage::userLoggedOut()
{
    chatThread->stop();
    if(currentChatWindow)
    {
        currentChatWindow->close();
    }
    QFile file("user.txt");
    file.remove();
    file.close();
    MainWindow * loginPage = new MainWindow();
    loginPage->show();
    this->close();
}
void ChatListPage::new_conversation(Conversation* conversation)
{
    QPushButton *button = new QPushButton("    "+conversation->name());
    connect(button,&QPushButton::clicked,conversation,&Conversation::show_conversation);
    connect(conversation,SIGNAL(show(Conversation*)),this,SLOT(showConversation(Conversation*)));
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    button->setFixedHeight(50);
    button->setStyleSheet("\
        QPushButton {\
                color : rgb(255 , 255, 255);\
                text-align:left;\
                border-radius: 0px;\
                border : none;\
                border-color: rgb(6, 118, 255);\
                background-color: rgb(12, 16, 27);\
        }\
        QPushButton:hover {\
                background-color: rgb(32,42,71); \
                border : none;\
                border-style: outset; \
                border-width: 2px;\
        }\
        QPushButton:pressed {\
                background-color: rgb(40,54,92);\
                border : none;\
                border-style: inset; \
                border-width: 2px;\
        }");
    chatsLayout->addWidget(button);
}


void ChatListPage::on_pushButton_clicked()
{
    qDebug() << "logout button clicked";
    if(chatThread->isRunning())
    {
        logOutFlag = true;
    }
    else
    {
        logOutFlag = false;
    }
    chatThread->stop();
    user->logout();
}


void ChatListPage::on_exitButton_clicked()
{
    chatThread->stop();
    this->close();
}

void ChatListPage::showConversation(Conversation* conv)
{
    ConversationWindow* window = new ConversationWindow(conv);
    currentChatWindow = window;
    window->exec();
}
void ChatListPage::on_minimizeButton_clicked()
{
    this->showMinimized();
}
void ChatListPage::mousePressEvent(QMouseEvent* event)
{
    if(!isMouseOnToolbar(event->pos()))return;
    dragPosition = event->globalPos() - frameGeometry().topLeft();
    event->accept();
}
void ChatListPage::mouseMoveEvent(QMouseEvent* event)
{
    if(!isMouseOnToolbar(event->pos()))return;
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}
bool ChatListPage::isMouseOnToolbar(QPoint mousePos)
{
    QRect toolbar(0,0,350,25);
    return toolbar.contains(mousePos);
}
void ChatListPage::sessionExpired()
{
    if(sessionExpiredFlag) {return; }
    sessionExpiredFlag = true;
    chatThread->stop();
    infoDialog* dialog = new infoDialog("Your token is expired\nTry logging in again",this);
    dialog->exec();
    delete dialog;
    userLoggedOut();
    sessionExpiredFlag = false;//unnecessary
}


void ChatListPage::on_menuToggleButton_clicked(bool checked)
{
    ui->menuToggleButton->setEnabled(false);
    if(showingMenu)
    {
        ui->scrollAreaWidgetContents->setEnabled(true);
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
    }
    else
    {
        ui->scrollAreaWidgetContents->setEnabled(false);
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
    }
}


void ChatListPage::on_pushButton_2_clicked()
{
    NewConversationWindow * window = new NewConversationWindow("channel");
    window->exec();
    delete window;
}

void ChatListPage::on_switchMode_toggled(bool checked)
{
    QRect left(124,462,20,20);
    QRect right(176,462,20,20);
    switchAnimation->setDuration(100);
    if(checked)
    {
        switchAnimation->setStartValue(right);
        switchAnimation->setEndValue(left);
        switchAnimation->start();
        chatThread->stop();
    }
    else
    {
        //        QtConcurrent::run(&ChatThread::start,chatThread);
        switchAnimation->setStartValue(left);
        switchAnimation->setEndValue(right);
        switchAnimation->start();
        chatThread->start();
    }
}

