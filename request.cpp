#include "request.h"
QJsonObject get(QString url, QUrlQuery params,bool print)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QUrl requestURL(url);
    requestURL.setQuery(params);
    QNetworkRequest request;
    request.setUrl(requestURL);
    QNetworkReply* reply = manager->get(request);
    if(print)qDebug() << "url: "<<requestURL.toDisplayString();
    QEventLoop eventLoop;
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();

    QJsonObject jsonObject;

    if (reply->error())
    {
        qDebug() << reply->errorString();
    }
    else
    {
        QByteArray response = reply->readAll();
        QJsonDocument doc(QJsonDocument::fromJson(response));
        jsonObject = doc.object();
        if(print)qDebug() << QString(doc.toJson(QJsonDocument::Compact)) <<"\n";
    }
    reply->deleteLater();
    delete manager;

    return jsonObject;
}
