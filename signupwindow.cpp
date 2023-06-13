#include "signupwindow.h"
#include "ui_signupwindow.h"

SignupWindow::SignupWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignupWindow)
{
    this->setStyleSheet("#{background-image: url(:/back/background.jpg);}");
    ui->setupUi(this);
}

SignupWindow::~SignupWindow()
{
    delete ui;
}
