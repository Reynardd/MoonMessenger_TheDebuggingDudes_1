#ifndef MESSAGERECT_H
#define MESSAGERECT_H

#include <QWidget>
#include <QTextEdit>
#include <QObject>
#include "message.h"
#include <QLabel>
#include <QMenu>
class DynamicRectangle : public QTextEdit
{
    Q_OBJECT
public:
    DynamicRectangle(Message* message,bool fromME,QWidget* parent = nullptr);
    void wheelEvent(QWheelEvent* event) override;
private:
    void onTextChanged();
    bool fromMe;
    QLabel* label;
};

class MessageRect : public QWidget
{
    Q_OBJECT
public:
    explicit MessageRect(Message* message,bool fromMe,QWidget *parent = nullptr);
private:
    bool fromMe;
    DynamicRectangle* messageRect;
    Message* message;
    QString conversationName;
private slots:
    void showContextMenu(const QPoint &);
signals:

};

#endif // MESSAGERECT_H
