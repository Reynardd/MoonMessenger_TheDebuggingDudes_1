#include "signuppage.h"
#include "ui_signuppage.h"

signuppage::signuppage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signuppage)
{
    ui->setupUi(this);
}

signuppage::~signuppage()
{
    delete ui;
}
