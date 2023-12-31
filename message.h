#ifndef MESSAGE_H
#define MESSAGE_H
#include <QTextStream>
#include <QObject>

class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(int id,QString sender,QString text,QString date,QObject *parent = nullptr);
    explicit Message(QString data,QObject* parent = nullptr);
    Message(Message& m);
    QString sender();
    QString text();
    QString toString();
    QString date();
    QString type();
    const int& id();
    bool isLiked,isDeleted;
    void toggleLiked();
private slots:
    void deleteMessage();
private:
    int _id;
    QString _sender;
    QString _text;
    QString _date;
signals:
    void wasLiked();
    void deleted();
};

#endif // MESSAGE_H
