#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>

class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(int id,QString sender,QString text,QString date,QObject *parent = nullptr);
    Message(Message& m);
    ~Message();
    QString toString();
    QString date();
private:
    int _id;
    QString _sender;
    QString _text;
    QString _date;
signals:

};

#endif // MESSAGE_H
