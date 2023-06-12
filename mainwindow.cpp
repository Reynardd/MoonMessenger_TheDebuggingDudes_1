#include "mainwindow.h"
#include "ui_mainwindow.h"

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

