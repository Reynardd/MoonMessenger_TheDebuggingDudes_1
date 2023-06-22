#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>

class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(QString sender,QString text,QString date,QObject *parent = nullptr);
    Message(Message& m);
    ~Message();
    QString toString();
    QString date();
private:
    QString _sender;
    QString _text;
    QString _date;
signals:

};

#endif // MESSAGE_H
