#ifndef MESSAGERECT_H
#define MESSAGERECT_H

#include <QWidget>
#include <QTextEdit>
#include <QObject>
#include "message.h"
class DynamicRectangle : public QTextEdit
{
    Q_OBJECT
public:
    DynamicRectangle(Message* message,bool fromME,QWidget* parent = nullptr);
    void wheelEvent(QWheelEvent* event) override;
};

class MessageRect : public QWidget
{
    Q_OBJECT
public:
    explicit MessageRect(Message* message,bool fromMe,QWidget *parent = nullptr);
private:
    DynamicRectangle* messageRect;
signals:

};

#endif // MESSAGERECT_H
