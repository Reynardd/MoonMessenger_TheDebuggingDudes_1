#include "signupwindow.h"
#include "ui_signupwindow.h"
#include "mainwindow.h"
#include "infodialog.h"
#include "request.h"
#include "yesnodialog.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
SignupWindow::SignupWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignupWindow)
{
    passwordStrength = 0;
    passwordMatch = false;
    ui->setupUi(this);
    ui->FName->hide();
    ui->label_6->hide();
    ui->label_8->hide();
    ui->label_9->hide();
    ui->cPassword->hide();
    ui->LName->hide();
    anim = new QPropertyAnimation(ui->signupButton,"geometry",this);
    anim->setDuration(250);
    anim->setStartValue(ui->signupButton->geometry());
    anim->setEndValue(QRect(45,268,ui->signupButton->geometry().width(),ui->signupButton->geometry().height()));
    anim->start();
    connect(anim,&QPropertyAnimation::finished,ui->FName,&QWidget::show);
    connect(anim,&QPropertyAnimation::finished,ui->label_6,&QWidget::show);
    connect(anim,&QPropertyAnimation::finished,ui->cPassword,&QWidget::show);
    connect(anim,&QPropertyAnimation::finished,ui->LName,&QWidget::show);
    connect(anim,&QPropertyAnimation::finished,ui->label_9,&QWidget::show);
    connect(anim,&QPropertyAnimation::finished,ui->label_8,&QWidget::show);
}

SignupWindow::~SignupWindow()
{
    delete ui;
}

void SignupWindow::on_craete_linkActivated(const QString &link)
{

    MainWindow* main = new MainWindow();
    main->show();
    this->close();
}


void SignupWindow::on_signupButton_clicked()
{
    ui->signupButton->setEnabled(false);
    QString username = ui->username->text();
    QString password = ui->password->text();
    QString name = ui->LName->text();
    if(username == "")
    {
        infoDialog* dialog = new infoDialog("Username Cannot be empty\nPlease Provide a Username",this);
        dialog->exec();
        ui->signupButton->setEnabled(true);
        return;
    }
    if(!passwordMatch && passwordStrength!= 0)
    {
        infoDialog* dialog = new infoDialog("You Passwords Don't Match\nPlease re-check them",this);
        ui->signupButton->setEnabled(true);
        dialog->exec();
        return;
    }
    if(passwordStrength==0)
    {
        infoDialog* dialog = new infoDialog("Password Cannot be Empty",this);
        dialog->exec();
        ui->signupButton->setEnabled(true);
        return;
    }
    if(passwordStrength<2)
    {
        YesNoDialog* dialog = new YesNoDialog("Your Password is very weak\nAre you sure You wanna Use it?",this);
        if(dialog->exec()==QDialog::Rejected)
        {
            ui->signupButton->setEnabled(true);
            return;
        }
    }
    QUrlQuery query;
    query.addQueryItem("username",username);
    query.addQueryItem("password",password);
    //if(name!="")query.addQueryItem("firstname",name);
    QJsonObject response = get("http://api.barafardayebehtar.ml:8080/signup",query);
    if(response.empty())
    {
        infoDialog *dialog = new infoDialog("Couldn't Connect to the Host!\nCheck your Internet Connection",this);
        dialog->exec();
        ui->signupButton->setEnabled(true);
        return;
    }
    if(response.value("code").toString()=="204")
    {
        infoDialog *dialog = new infoDialog("This Username is already in Use!\nPlease Use Another one",this);
        dialog->exec();
        ui->signupButton->setEnabled(true);
        return;
    }
    if(response.value("code")=="200")
    {
        infoDialog *dialog = new infoDialog("Signed Up Succesfully!\nYou'll we be Navigated to Login Page",this);
        dialog->exec();
        ui->signupButton->setEnabled(true);
        MainWindow* loginPage = new MainWindow();
        loginPage->show();
        this->close();
        return;
    }
    else
    {
        infoDialog *dialog = new infoDialog("Something went Wrong\nServer Message:"+response.value("message").toString(),this);
        dialog->exec();
        ui->signupButton->setEnabled(true);
        return;
    }
}


void SignupWindow::on_password_textChanged(const QString &arg1)
{
    if(ui->cPassword->text() == "")
    {
        ui->label_9->setText("<html><head/><body><p><span style=\" color:#ffffff;\">________________</span></p></body></html>");
        passwordMatch = false;
    }
    else if(ui->password->text() == ui->cPassword->text())
    {
        ui->label_9->setText("<html><head//><body><p><span style=\" color:#00ff00;\">________________<//span><//p><//body><//html>");
        passwordMatch = true;
    }
    else
    {
        ui->label_9->setText("<html><head/><body><p><span style=\" color:#ff0000;\">________________</span></p></body></html>");
        passwordMatch = false;
    }

    if(arg1 == "")
    {
        ui->label_8->setText("<html><head/><body><p><span style=\" color:#ffffff;\">________________</span></p></body></html>");
        passwordStrength = 0;
        return;
    }
    QRegularExpression veryWeak("^(?:[a-zA-Z]{1,4}|\\d{1,4})$");
    QRegularExpression weak("^(?=[a-zA-Z0-9]{1,4}$)(?=.*[a-zA-Z])(?=.*\\d)");
    QRegularExpression moderate("^(?=.*[a-zA-Z])(?=.*\\d).{5,}$");
    QRegularExpression strong("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).{5,}$");
    QRegularExpressionMatch m;
    m = strong.match(arg1);
    if(m.hasMatch()){
        ui->label_8->setText("<html><head//><body><p><span style=\" color:#00ff00;\">________________<//span><//p><//body><//html>");
        passwordStrength = 4;
        return;
    }
    m = moderate.match(arg1);
    if(m.hasMatch())
    {
        ui->label_8->setText("<html><head/><body><p><span style=\" color:#ffff00;\">____________</span><span style=\" color:#ffffff;\">____</span></p></body></html>");
        passwordStrength = 3;
        return;
    }
    m = weak.match(arg1);
    if(m.hasMatch())
    {
        ui->label_8->setText("<html><head/><body><p><span style=\" color:#ffa500;\">________</span>________</p></body></html>");
        passwordStrength = 2;
        return;
    }
    m = veryWeak.match(arg1);
    if(m.hasMatch())
    {
        ui->label_8->setText("<html><head/><body><p><span style=\" color:#ff0000;\">____</span>____________</p></body></html>");
        passwordStrength = 1;
        return;
    }

}

void SignupWindow::on_cPassword_textChanged(const QString &arg1)
{
    if(arg1 == "")
    {
        ui->label_9->setText("<html><head/><body><p><span style=\" color:#ffffff;\">________________</span></p></body></html>");
        passwordMatch = false;
    }
    else if(ui->password->text() == ui->cPassword->text())
    {
        ui->label_9->setText("<html><head//><body><p><span style=\" color:#00ff00;\">________________<//span><//p><//body><//html>");
        passwordMatch = true;
    }
    else
    {
        ui->label_9->setText("<html><head/><body><p><span style=\" color:#ff0000;\">________________</span></p></body></html>");
        passwordMatch = false;
    }
}

