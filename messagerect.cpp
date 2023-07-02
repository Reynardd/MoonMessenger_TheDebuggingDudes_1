#include "messagerect.h"
#include <QLabel>
#include <QWheelEvent>
#include <QTimer>
#include <QEventLoop>
#include <QFontMetrics>
QString extractClock(QString date)
{
    QString res;
    for(int i =11;i<16;i++) { res+=date[i]; }
    return res;
}
DynamicRectangle::DynamicRectangle(Message* message,bool fromMe,QWidget* parent) : QTextEdit(parent)
{

    QString text = message->text();
    QString sender = message->sender();
    QString date = message->date();
    this->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setText(text);
    QString style ="QTextEdit{background-color: #0676FF;color:white;\
        border: 1px solid #e5e5ea;border-top-left-radius:10px;\
        border-top-right-radius:8px;\
        padding-top: 5px;padding-left:5px;\
        padding-right:5px;padding-bottom:15px;";
    QLabel* label = new QLabel(this);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    label->setStyleSheet("color:#C3C3C3;padding-right:5px;padding-bottom:1px");

    label->setText(sender +" "+ extractClock(date));
    label->adjustSize();
    if(fromMe)
    {
        style+="border-bottom-right-radius:10px;}";
        label->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
        this->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    }
    else
    {
        this->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
        style+="border-bottom-left-radius:10px}";

        label->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    }

    this->setStyleSheet(style);


    int width = this->fontMetrics().boundingRect(text).width();
    if(width < 70) { this->setFixedWidth(100);}
    else if (width > 220) { this->setFixedWidth(250);}
    else { this->setFixedWidth(width + 30);}



    if(width>220)
    {
    QFontMetrics metrics(this->font());

    int totalHeight = 0;
    QStringList lines = this->toPlainText().split("\n");
    qDebug() << "multiLine";
    for (const QString& line : lines)
    {
        QRect rect = metrics.boundingRect(QRect(0, 0, 220, 0), Qt::AlignLeft | Qt::TextWrapAnywhere, line);
        if(line=="")continue;
        totalHeight += rect.height() + 7;
    }
        this->setFixedHeight(totalHeight+35);
    }
    else
    {
        this->setFixedHeight(40);
    }
    label->setGeometry(0,this->height()-label->height(),this->width(),label->height());
}
void DynamicRectangle::wheelEvent(QWheelEvent* event)
{
    event->ignore();
}
MessageRect::MessageRect(Message* message,bool fromMe,QWidget *parent)
    : QWidget{parent}
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    messageRect = new DynamicRectangle(message,fromMe,this);
    this->setGeometry(0,0,messageRect->width()+10,messageRect->height());
    messageRect->show();
    if(!fromMe){messageRect->move(messageRect->x()+5,messageRect->y());}
    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    this->setFixedSize(size());
}

