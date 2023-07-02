#include "joinconversationwindow.h"
#include "ui_joinconversationwindow.h"

JoinConversationWindow::JoinConversationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::JoinConversationWindow)
{
    ui->setupUi(this);
}

JoinConversationWindow::~JoinConversationWindow()
{
    delete ui;
}
