#include "messagerect.h"
#include <QLabel>
#include <QWheelEvent>
#include <QTimer>
#include <QEventLoop>
#include <QFontMetrics>
#include "user.h"
#include "conversationwindow.h"
extern User* user;
QString extractClock(QString date)
{
    QString res;
    for(int i =11;i<16;i++) { res+=date[i]; }
    return res;
}
DynamicRectangle::DynamicRectangle(Message* message,bool fromMe,QWidget* parent) :
    QTextEdit(parent),fromMe(fromMe)
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
    label = new QLabel(this);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    label->setStyleSheet("color:#C3C3C3;padding-right:5px;padding-left:5px;padding-bottom:1px");

    label->setText(sender +" "+ extractClock(date));
    label->adjustSize();
    if(fromMe)
    {
        this->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
        style+="border-bottom-left-radius:10px}";
        label->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    }
    else
    {
        style+="border-bottom-right-radius:10px;}";
        label->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
        this->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
    }

    this->setStyleSheet(style);
    int width = this->fontMetrics().boundingRect(this->toPlainText()).width();
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
void DynamicRectangle::onTextChanged()
{

    int width = this->fontMetrics().boundingRect(this->toPlainText()).width();
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
    : QWidget{parent},fromMe(fromMe),message(message)
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    conversationName = qobject_cast<ConversationWindow*>(parent)->conversationName;
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));

    messageRect = new DynamicRectangle(message,fromMe,this);
    this->setGeometry(0,0,messageRect->width()+10,messageRect->height());
    messageRect->show();
    if(!fromMe){messageRect->move(messageRect->x()+5,messageRect->y());}
    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    this->setFixedSize(size());
}

void MessageRect::showContextMenu(const QPoint &pos)
{
    if(!fromMe)
    {
        QMenu contextMenu(tr("Context menu"), this);

        QAction action1("Like", this);
        connect(&action1, &QAction::triggered,[&](){
            qDebug() << "liking message #"+QString::number(message->id()) << "in conversation" << conversationName ;
        });
        contextMenu.addAction(&action1);
        contextMenu.exec(mapToGlobal(pos));
    }


}
