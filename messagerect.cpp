#include "messagerect.h"
#include <QLabel>
#include <QWheelEvent>
#include <QTimer>
#include <QEventLoop>
#include <QFontMetrics>
#include "user.h"
#include "conversationwindow.h"
#include <QFont>
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
    label = new QLabel(this);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QString style;
    like = new QWidget(this);
    like->setStyleSheet("image:url(:/label/likeIcon.svg)");

    label->setText(sender +"  "+ extractClock(date));
    label->adjustSize();
    if(fromMe)
    {
        style = "QTextEdit{background-color: qlineargradient(spread:pad, x1:0, y1:0.244, x2:1,\
                y2:0.801136, stop:0 rgba(162, 44, 181, 255), stop:1 rgba(93, 19, 161, 255));color:white;\
                border-radius:10px;}";
        this->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
        label->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        labelStyle="color:#C3C3C3;";
        //label->setStyleSheet();
    }
    else
    {
        style = "QTextEdit{background-color: qlineargradient(spread:pad, x1:0, y1:0.244, x2:1,\
                y2:0.801136, stop:0 rgba(39, 33, 43, 255), stop:1 rgba(39, 33, 43, 255));color:white;\
                border:none;border-radius:10px;}";
        label->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
        this->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
        labelStyle="color:#212121;";
        labelStyle="color:#C3C3C3;";
        //label->setStyleSheet();
    }
    label->setStyleSheet(labelStyle+"padding-right:5px;padding-left:5px;padding-bottom:1px");
    isLiked = false;
    like->hide();
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
        this->setFixedHeight(45);
    }
    QFont font = label->font();
    if(fromMe) { like->setGeometry(5,this->height()-12,10,10); }
    else { like->setGeometry(this->width()-15,this->height()-12,10,10);}
    font.setPointSize(8);
    label->setFont(font);
    label->setGeometry(0,this->height()-label->height(),this->width(),label->height());

    if(message->isLiked) { handleLike(); }
    if(message->isEdited) {edit(message->editedText());}
}
void DynamicRectangle::handleLike()
{
    if(isLiked)
    {
        isLiked = false;
        like->hide();
        label->setStyleSheet(labelStyle+"padding-right:5px;padding-left:5px;padding-bottom:1px");
    }
    else
    {
        isLiked = true;
        like->show();
        label->setStyleSheet(labelStyle+"padding-right:15px;padding-left:15px;padding-bottom:1px");
    }
}
void DynamicRectangle::onTextChanged()
{
}
void DynamicRectangle::wheelEvent(QWheelEvent* event)
{
    event->ignore();
}
void DynamicRectangle::edit(QString text)
{
    this->setFixedHeight(0);
}
MessageRect::MessageRect(Message* message,bool fromMe,QWidget *parent)
    : QWidget{parent},fromMe(fromMe),message(message)
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    //this->setAttribute(Qt::WA_TranslucentBackground);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    conversationName = qobject_cast<ConversationWindow*>(parent)->conversationName;
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(showContextMenu(const QPoint &)));
    QWidget* tail = new QWidget(this);

    //tail->setAttribute(Qt::WA_TranslucentBackground,true);

    tail->setFixedSize(10,12);
    messageRect = new DynamicRectangle(message,fromMe,this);
    this->setGeometry(0,0,messageRect->width()+10,messageRect->height());
    connect(message,&Message::wasLiked,messageRect,&DynamicRectangle::handleLike);
    connect(message,&Message::edited,[&](){this->setFixedHeight(0);});
    messageRect->show();
    if(!fromMe){messageRect->move(messageRect->x()+10,messageRect->y());}
    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    this->setFixedSize(size());
    if(!fromMe)
    {
        tail->setGeometry(5,this->height()-15,10,12);
        tail->setStyleSheet("image:url(:/label/bubbleTailLeft.svg);");
    }
    else
    {
        tail->setGeometry(this->width()-15,this->height()-15,10,12);
        tail->setStyleSheet("image:url(:/label/bubbleTail.svg);");
    }
    tail->show();
}

void MessageRect::showContextMenu(const QPoint &pos)
{
    QMenu contextMenu(tr("Context menu"), this);

    QAction action1("Like", this);
    QAction action2("Delete", this);
    connect(&action1, &QAction::triggered,[&](){
        qDebug() << "liking message #"+QString::number(message->id()) << "in conversation" << conversationName ;
        user->sendMessage(conversationName,"user","#SERVERCOMMAND-LIKE"+QString::number(message->id()));
    });
    connect(&action2, &QAction::triggered,[&](){
        qDebug() << "editing message #"+QString::number(message->id()) << "in conversation" << conversationName ;
        user->sendMessage(conversationName,"user","#SERVERCOMMAND-EDIT:"+QString::number(message->id())+"-Edited Message");
    });
    if(!fromMe)contextMenu.addAction(&action1);
    else contextMenu.addAction(&action2);
    contextMenu.exec(mapToGlobal(pos));


}
