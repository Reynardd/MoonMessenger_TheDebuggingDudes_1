#include "infodialog.h"
#include "ui_infodialog.h"

infoDialog::infoDialog(QString text,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::infoDialog)
{
    ui->setupUi(this);
    this->setStyleSheet("#centralwidget{background-image: url(:/back/background.jpg);border: 1px solid white;border-radius: 10px}");
    setWindowFlag(Qt::FramelessWindowHint);
    ui->plainTextEdit->appendPlainText(text);
    setAttribute(Qt::WA_TranslucentBackground);
}

infoDialog::~infoDialog()
{
    delete ui;
}

void infoDialog::on_pushButton_clicked()
{
    this->close();
}
void infoDialog::mousePressEvent(QMouseEvent* event)
{
    dragPosition = event->globalPos() - frameGeometry().topLeft();
    event->accept();
}
void infoDialog::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

