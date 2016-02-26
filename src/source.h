#ifndef SOURCE_H
#define SOURCE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QPair>
#include <QMap>
#include <QMultiMap>
#include <QVariant>

#include "makesvg.h"
#include "buspositions.h"

class source : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString sourceString READ sourceString WRITE setSourceString NOTIFY sourceStringChanged)
    Q_PROPERTY(int reqCount READ reqCount WRITE setReqCount NOTIFY reqCountChanged)
    Q_PROPERTY(BusPositions* busPositions READ busPositions)


public:
    explicit source(QObject *parent = 0);

    Q_INVOKABLE void askPositions();
    Q_INVOKABLE void getFormattedString (QString s);
    Q_INVOKABLE void printData();
    Q_INVOKABLE void setXY(double xMin, double xMax, double yMin, double yMax);
    Q_INVOKABLE void updateMap();



    QString sourceString() const;

    int reqCount() const;

    BusPositions * busPositions()
    {
        return m_busPositions;
    }

signals:


    void sourceStringChanged(QString sourceString);

    void reqCountChanged(int reqCount);
    void newMap (QString mapName);

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
    typedef QPair<double,double>   Pos;

    QMultiMap<QString,PosDataType> m_posMap;
    QMultiMap<Pos,QString>         m_positions;
    BusPositions                  * m_busPositions;

    double latMin;
    double latMax;
    double lonMin;
    double lonMax;
    double xRange;
    double yRange;

    MakeSVG  m_fileMaker;
};



#endif // SOURCE_H
