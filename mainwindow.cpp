#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFontDatabase>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("#centralwidget{background-image: url(:/back/backgroundWin.jpg);}");

}

MainWindow::~MainWindow()
{
    delete ui;
}

