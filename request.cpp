#include "request.h"
#include <QTimer>

QJsonObject get(QString url, QUrlQuery params)
{
    QNetworkAccessManager manager;
    QUrl requestURL(url);
    requestURL.setQuery(params);
    QNetworkRequest request(requestURL);
    QNetworkReply* reply = manager.get(request);
    //qDebug() << "url: " << requestURL.toDisplayString();
    QEventLoop eventLoop;
    QTimer timeoutTimer;
    timeoutTimer.setSingleShot(true);
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    QObject::connect(&timeoutTimer, &QTimer::timeout, &eventLoop, &QEventLoop::quit);
    timeoutTimer.start(10000);//timeout duratuin 5 seconds
    eventLoop.exec();
    QJsonObject jsonObject;
    if (timeoutTimer.isActive()) {
        timeoutTimer.stop();
        if (reply->error() != QNetworkReply::NoError) {
            qDebug() << "Error: " << reply->errorString();
        } else {
            QByteArray response = reply->readAll();
            QJsonDocument doc = QJsonDocument::fromJson(response);
            if (!doc.isNull()) {
                if (doc.isObject()) {
                    jsonObject = doc.object();
                    //qDebug() << QString(doc.toJson(QJsonDocument::Compact)) << "\n";
                } else {
                    qDebug() << "Error: Invalid JSON object received";
                }
            } else {
                qDebug() << "Error: Failed to parse JSON response";
            }
        }
    } else {
        qDebug() << "Error: Request timed out";
    }
    reply->deleteLater();
    return jsonObject;
}
