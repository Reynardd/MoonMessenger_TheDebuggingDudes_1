#include "signupwindow.h"
#include "ui_signupwindow.h"
#include "mainwindow.h"
SignupWindow::SignupWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignupWindow)
{

    ui->setupUi(this);
    ui->label_7->hide();
    ui->label_6->hide();
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

