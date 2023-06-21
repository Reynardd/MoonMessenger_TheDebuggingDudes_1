#include "signupwindow.h"
#include "ui_signupwindow.h"
#include "mainwindow.h"
#include "infodialog.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
SignupWindow::SignupWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignupWindow)
{

    ui->setupUi(this);
    ui->label_7->hide();
    ui->label_6->hide();
    ui->label_8->hide();
    ui->label_9->hide();
    ui->cPassword->hide();
    ui->name->hide();
    anim = new QPropertyAnimation(ui->signupButton,"geometry",this);
    anim->setDuration(250);
    anim->setStartValue(ui->signupButton->geometry());
    anim->setEndValue(QRect(45,268,ui->signupButton->geometry().width(),ui->signupButton->geometry().height()));
    anim->start();
    connect(anim,&QPropertyAnimation::finished,ui->label_7,&QWidget::show);
    connect(anim,&QPropertyAnimation::finished,ui->label_6,&QWidget::show);
    connect(anim,&QPropertyAnimation::finished,ui->cPassword,&QWidget::show);
    connect(anim,&QPropertyAnimation::finished,ui->name,&QWidget::show);
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
    qDebug() << ui->label_8->text();
    //<html><head/><body><p><span style=" color:#ff0000;">____</span>____________</p></body></html>
    //<html><head/><body><p><span style=" color:#ffa500;">________</span>________</p></body></html>
    //<html><head/><body><p><span style=" color:#ffff00;">____________</span>____</p></body></html>
    //<html><head/><body><p><span style=" color:#00ff00;">________________</span></p></body></html>
}


void SignupWindow::on_password_textChanged(const QString &arg1)
{
    if(ui->cPassword->text() == "")
    {
        ui->label_9->setText("<html><head/><body><p><span style=\" color:#ffffff;\">________________</span></p></body></html>");
    }
    else if(ui->password->text() == ui->cPassword->text())
    {
        ui->label_9->setText("<html><head//><body><p><span style=\" color:#00ff00;\">________________<//span><//p><//body><//html>");
    }
    else
    {
        ui->label_9->setText("<html><head/><body><p><span style=\" color:#ff0000;\">________________</span></p></body></html>");
    }

    if(arg1 == "")
    {
        ui->label_8->setText("<html><head/><body><p><span style=\" color:#ffffff;\">________________</span></p></body></html>");
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
        return;
    }
    m = moderate.match(arg1);
    if(m.hasMatch())
    {
        ui->label_8->setText("<html><head/><body><p><span style=\" color:#ffff00;\">____________</span><span style=\" color:#ffffff;\">____</span></p></body></html>");
        return;
    }
    m = weak.match(arg1);
    if(m.hasMatch())
    {
        ui->label_8->setText("<html><head/><body><p><span style=\" color:#ffa500;\">________</span>________</p></body></html>");
        return;
    }
    m = veryWeak.match(arg1);
    if(m.hasMatch())
    {
        ui->label_8->setText("<html><head/><body><p><span style=\" color:#ff0000;\">____</span>____________</p></body></html>");
        return;
    }

}

void SignupWindow::on_cPassword_textChanged(const QString &arg1)
{
    if(arg1 == "")
    {
        ui->label_9->setText("<html><head/><body><p><span style=\" color:#ffffff;\">________________</span></p></body></html>");
    }
    else if(ui->password->text() == ui->cPassword->text())
    {
        ui->label_9->setText("<html><head//><body><p><span style=\" color:#00ff00;\">________________<//span><//p><//body><//html>");
    }
    else
    {
        ui->label_9->setText("<html><head/><body><p><span style=\" color:#ff0000;\">________________</span></p></body></html>");
    }
}

