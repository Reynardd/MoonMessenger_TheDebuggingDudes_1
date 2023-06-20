#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signupwindow.h"
#include "chatlistpage.h"
#include "infodialog.h"
#include <QFontDatabase>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("#centralwidget{background-image: url(:/back/background.jpg);}");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_craete_linkActivated(const QString &link)
{
    SignupWindow * signUp = new SignupWindow();
    signUp->show();
    this->close();
}


void MainWindow::on_loginButton_clicked()
{
    //this is for test only
//    ChatListPage * chatList = new ChatListPage();
//    chatList->show();
    QString username = ui->username->text(),password = ui->password->text();
    infoDialog *dialog = new infoDialog("Login info: "+username+"\n"+password);
    dialog->exec();
}

