#ifndef REQUEST_H
#define REQUEST_H
#include <QJsonObject>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QUrlQuery>
#include <QUrl>
#include <QString>
#include <QJsonDocument>
#include <QEventLoop>
QJsonObject get(QString url,QUrlQuery params);
#endif // REQUEST_H
