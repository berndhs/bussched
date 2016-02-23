#ifndef SOURCE_H
#define SOURCE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

class source : public QObject
{
    Q_OBJECT


public:
    explicit source(QObject *parent = 0);

    Q_INVOKABLE void askPositions();


signals:


public slots:

    void gotPosReply();

private:

    QNetworkAccessManager qnam;

    QNetworkRequest  positionReq;
    QNetworkRequest  scheduleReq;
    QNetworkRequest  staticReq;

    QNetworkReply *posReply;

};

#endif // SOURCE_H
