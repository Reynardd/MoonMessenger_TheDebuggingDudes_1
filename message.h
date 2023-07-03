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
    QString editedText();
    const int& id();
    bool isLiked,isEdited;
    void toggleLiked();
private slots:
    void edit(QString);
private:
    int _id;
    QString _sender;
    QString _text;
    QString _date;
    QString _newText;
signals:
    void wasLiked();
    void edited(QString);
};

#endif // MESSAGE_H
