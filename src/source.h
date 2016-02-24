#ifndef SOURCE_H
#define SOURCE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QMap>
#include <QMultiMap>
#include <QVariant>

class source : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString sourceString READ sourceString WRITE setSourceString NOTIFY sourceStringChanged)
    Q_PROPERTY(int reqCount READ reqCount WRITE setReqCount NOTIFY reqCountChanged)


public:
    explicit source(QObject *parent = 0);

    Q_INVOKABLE void askPositions();
    Q_INVOKABLE void getFormattedString (QString s);
    Q_INVOKABLE void printData();


    QString sourceString() const;

    int reqCount() const;

signals:


    void sourceStringChanged(QString sourceString);

    void reqCountChanged(int reqCount);

public slots:

    void gotPosReply();
    void gotSchedReply();
    void gotStaticReply();

    void setSourceString(QString sourceString);

    void setReqCount(int reqCount);

private:

    void pickApartPos (QByteArray theData);

    QNetworkAccessManager qnam;

    QNetworkRequest  positionReq;
    QNetworkRequest  scheduleReq;
    QNetworkRequest  staticReq;

    QNetworkReply *posReply;
    QNetworkReply *schedReply;
    QNetworkReply *staticReply;

    QString m_sourceString;
    int m_reqCount;

    QString m_posData;
    QString m_schedData;
    QString m_staticData;


    typedef QMap<QString,QVariant> PosDataType;

    QMultiMap<QString,PosDataType> m_posMap;
};



#endif // SOURCE_H
