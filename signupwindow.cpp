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
    ui->cPassword->hide();
    ui->LName->hide();
    ui->FNameBorder->hide();
    ui->LNameBorder->hide();
    ui->confirmBorder->hide();
    anim = new QPropertyAnimation(ui->signupButton,"geometry",this);
    anim->setDuration(250);
    anim->setStartValue(ui->signupButton->geometry());
    anim->setEndValue(QRect(45,316,ui->signupButton->geometry().width(),ui->signupButton->geometry().height()));
    anim->start();
    connect(anim,&QPropertyAnimation::finished,[&](){
        ui->FNameBorder->show();
        ui->LNameBorder->show();
        ui->confirmBorder->show();
        ui->LName->show();
        ui->FName->show();
        ui->cPassword->show();
    });
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

void SignupWindow::passwordStrengthHandler(QString strength)
{
    if(strength=="empty")
    {
        ui->passwordBorder->setStyleSheet("background:none;image: url(:/label/lineEditBorderPassword.svg);");
        ui->password->setStyleSheet("background-color:transparent;border: none;padding-left:24px;color:white;");
        passwordStrength = 0;
        return;
    }
    if(strength=="strong")
    {
        ui->passwordBorder->setStyleSheet("background:none;image: url(:/label/lineEditBorderPasswordGreen.svg);");
        ui->password->setStyleSheet("background-color:transparent;border: none;padding-left:24px;color:green;");
        passwordStrength = 4;
        return;
    }
    if(strength=="moderate")
    {
        ui->passwordBorder->setStyleSheet("background:none;image: url(:/label/lineEditBorderPasswordYellow.svg);");
        passwordStrength = 3;
        ui->password->setStyleSheet("background-color:transparent;border: none;padding-left:24px;color:yellow;");
        return;
    }
    if(strength=="weak")
    {
        ui->passwordBorder->setStyleSheet("background:none;image: url(:/label/lineEditBorderPasswordOrange.svg);");
        passwordStrength = 2;
        ui->password->setStyleSheet("background-color:transparent;border: none;padding-left:24px;color:orange;");
        return;
    }
    if(strength=="veryWeak")
    {
        ui->passwordBorder->setStyleSheet("background:none;image: url(:/label/lineEditBorderPasswordRed.svg);");
        passwordStrength = 1;
        ui->password->setStyleSheet("background-color:transparent;border: none;padding-left:24px;color:red;");
        return;
    }
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

QString passwordStrengthChecker(QString password)
{
    if(password=="")
    {
        return "empty";
    }
    //QRegularExpression veryWeak("^(?:[a-zA-Z]{1,4}|\\d{1,4})$");
    //QRegularExpression weak("^(?=[a-zA-Z0-9]{1,4}$)(?=.*[a-zA-Z])(?=.*\\d)");
    //QRegularExpression moderate("^(?=.*[a-zA-Z])(?=.*\\d).{5,}$");
    //QRegularExpression strong("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).{5,}$");
    QRegularExpression veryWeak("^(?:[a-zA-Z]{1,4}|\\d{1,4})$");
    QRegularExpression weak("^(?:[a-zA-Z]+|\\d+){5,}$");
    QRegularExpression weak_2("^(?=.*[a-zA-Z])(?=.*\\d)[a-zA-Z\\d]{1,4}$");
    QRegularExpression moderate("^(?=.*[a-zA-Z])(?=.*\\d)[a-zA-Z\\d]{5,}$");
    QRegularExpression strong("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{5,}$");



    QRegularExpressionMatch m;
    m = strong.match(password);
    if(m.hasMatch()){
        return "strong";
    }
    m = moderate.match(password);
    if(m.hasMatch())
    {

        return "moderate";
    }
    m = weak.match(password);
    if(m.hasMatch())
    {

        return "weak";
    }
    m = weak_2.match(password);
    if(m.hasMatch())
    {

        return "weak";
    }
    m = veryWeak.match(password);
    if(m.hasMatch())
    {

        return "veryWeak";
    }
    return "empty";
}
void SignupWindow::passwordMatchHandler()
{
    if(ui->cPassword->text()=="")
    {
        passwordMatch = false;
        ui->confirmBorder->setStyleSheet("background:none;image: url(:/label/lineEditBorderConfirm.svg);");
        ui->cPassword->setStyleSheet("background-color:transparent;border: none;padding-left:24px;color:white;");
        return;
    }
    if(ui->cPassword->text()==ui->password->text())
    {
        passwordMatch = true;
        ui->confirmBorder->setStyleSheet("background:none;image: url(:/label/lineEditBorderCnfirmGreen.svg);");
        ui->cPassword->setStyleSheet("background-color:transparent;border: none;padding-left:24px;color:green;");
        return;
    }
    passwordMatch = false;
    ui->confirmBorder->setStyleSheet("background:none;image: url(:/label/lineEditBorderConfirmRed.svg);");
    ui->cPassword->setStyleSheet("background-color:transparent;border: none;padding-left:24px;color:red;");

}
void SignupWindow::on_password_textChanged(const QString &arg1)
{
    passwordMatchHandler();
    passwordStrengthHandler(passwordStrengthChecker(arg1));
}

void SignupWindow::on_cPassword_textChanged(const QString &arg1)
{
    passwordMatchHandler();
}

