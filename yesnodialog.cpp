#include "yesnodialog.h"
#include "ui_yesnodialog.h"

YesNoDialog::YesNoDialog(QString text,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::YesNoDialog)
{
    ui->setupUi(this);
    this->setStyleSheet("#centralwidget{background-image: url(:/back/background.jpg);border: 1px solid white;border-radius: 10px}");
    setWindowFlag(Qt::FramelessWindowHint);
    ui->plainTextEdit->appendPlainText(text);
    setAttribute(Qt::WA_TranslucentBackground);
    QTextOption option = ui->plainTextEdit->document()->defaultTextOption();
    option.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->plainTextEdit->document()->setDefaultTextOption(option);
}

YesNoDialog::~YesNoDialog()
{
    delete ui;
}
void YesNoDialog::mousePressEvent(QMouseEvent* event)
{
    dragPosition = event->globalPos() - frameGeometry().topLeft();
    event->accept();
}
void YesNoDialog::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}
int YesNoDialog::exec()
{
    return QDialog::exec();
}

void YesNoDialog::on_yesButton_clicked()
{
    accept();
}


void YesNoDialog::on_noButton_clicked()
{
    reject();
}

