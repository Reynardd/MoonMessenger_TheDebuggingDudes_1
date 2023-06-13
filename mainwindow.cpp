#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signupwindow.h"
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

