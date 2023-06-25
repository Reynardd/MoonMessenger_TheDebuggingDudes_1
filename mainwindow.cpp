#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signupwindow.h"
#include "chatlistpage.h"
#include "request.h"
#include "infodialog.h"
#include <QFontDatabase>
#include "yesnodialog.h"
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
    ui->loginButton->setEnabled(false);
    QString username = ui->username->text(),password = ui->password->text();
    QUrlQuery query;
    query.addQueryItem("username",username);
    query.addQueryItem("password",password);
    QJsonObject response = get("http://api.barafardayebehtar.ml:8080/login",query);
    if(response.empty())
    {
        infoDialog *dialog = new infoDialog("Couldn't Connect to the Host!\nCheck your Internet Connection",this);
        dialog->exec();
        ui->loginButton->setEnabled(true);
        return;
    }
    if(response.value("token")==QJsonValue::Undefined)
    {
        if(response.value("message").toString()=="You are already logged in!")
        {
            YesNoDialog *dialog = new YesNoDialog("A Session has already logged in to this Account\nDo you wish to terminate them?",this);
            int r = dialog->exec();
            if(r==QDialog::Accepted)
            {
                QJsonObject response = get("http://api.barafardayebehtar.ml:8080/logout",query);
                if(response.empty())
                {
                    infoDialog *dialog = new infoDialog("Couldn't Connect to the Host!\nCheck your Internet Connection");
                    dialog->exec();
                }
                else if(response.value("code").toString()=="200")
                {
                    infoDialog *dialog = new infoDialog("The Previous Session has Been terminated\nEnjoy Logging in :)");
                    dialog->exec();
                    on_loginButton_clicked();
                }
                else
                {
                    infoDialog *dialog = new infoDialog("Something went Wrong\nServer Message: "+response.value("message").toString());
                    dialog->exec();
                }
            }

            ui->loginButton->setEnabled(true);
            return;
        }
        infoDialog *dialog = new infoDialog("Server Message: "+response.value("message").toString(),this);
        dialog->exec();
        ui->loginButton->setEnabled(true);
        return;
    }
    ChatListPage * chatList = new ChatListPage(username,password,response.value("token").toString());
    chatList->show();
    this->close();

}

