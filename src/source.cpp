#include "source.h"
#include <QDebug>
#include <QUrl>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVariant>
#include <QVariantMap>
#include <QStringList>
#include <QByteArray>
#include <QList>
#include <iostream>

void reportc (const char* s)
{
      qDebug() << s;
}
void reportss (std::string s)
{
      qDebug() << s.c_str() ;
}
void reportqs (QString s)
{
      qDebug() << s;
}
void report (int i)
{
      qDebug() << i ;
}
void report (QStringList sl)
{
    qDebug() << sl ;
}
void reportba (QByteArray ba)
{
    qDebug() << ba.length() << " bytes " << ba ;
}


source::source(QObject *parent) : QObject(parent),
    positionReq(QUrl("http://api.octa.net/gtfsrealtime/protobuf/vehiclepositions.aspx?format=json")),
    scheduleReq(QUrl("http://api.octa.net/gtfsrealtime/protobuf/tripupdates.aspx?format=json")),
    staticReq(QUrl("http://api.octa.net/gtfsrealtime/protobuf/servicealerts.aspx?format=json")),
    m_reqCount(0),
    m_busPositions(0),
    latMin(90),
    latMax(-90),
    lonMin(180),
    lonMax(-180)
{
    reportc(Q_FUNC_INFO);
    m_busPositions = new BusPositions(this);
}

void source::askPositions()
{
    posReply = qnam.get (positionReq);
    connect(posReply,SIGNAL(finished()),this,SLOT(gotPosReply()));
    schedReply = qnam.get (scheduleReq);
    connect(schedReply,SIGNAL(finished()),this,SLOT(gotSchedReply()));
    staticReply = qnam.get (staticReq);
    connect(staticReply,SIGNAL(finished()),this,SLOT(gotStaticReply()));
}

void source::getFormattedString(QString s)
{
    qDebug() << "string \n" << s;
}

void source::printData()
{

    qDebug() << Q_FUNC_INFO;
    qDebug () << " all the same " << ((m_posData == m_schedData) && (m_posData == m_staticData));
}

void source::setXY(double xMin, double xMax, double yMin, double yMax)
{
    double latRange = latMax - latMin;
    double lonRange = lonMax - lonMin;
    double xRange = xMax - xMin;
    double yRange = yMax - yMin;
    double latScale = latRange / yRange;
    double lonScale = lonRange / xRange;
    m_busPositions->setScaleLat(latScale);
    m_busPositions->setScaleLon(lonScale);
    m_busPositions->signalDataChanged();
}

QString source::sourceString() const
{
    return m_sourceString;
}

int source::reqCount() const
{
    return m_reqCount;
}

void source::pickApartPos (QByteArray theData)
{
    qDebug() << Q_FUNC_INFO ;
    QJsonDocument doc = QJsonDocument::fromJson(theData);
    QJsonObject obj = doc.object();
    QVariantMap map = obj.toVariantMap();
    QVariantMap::iterator mit = map.find ("entity");
    QVariantList vl = mit->toList();
    int e(0);
    for (auto vlit = vl.begin(); vlit != vl.end(); ++ vlit) {
//        qDebug() << "entry " << e << "----------------------";
        QVariantMap dataMap = vlit->toMap();
//        qDebug() << "id\n" << dataMap["id"] ;
        QVariantMap vehicleMap = dataMap["vehicle"].toMap();
        QVariantMap posMap = vehicleMap["position"].toMap();
        double lat = posMap["latitude"].toDouble();
        double lon = posMap["longitude"].toDouble();
        if (lat < latMin) latMin = lat;
        if (lat > latMax) latMax = lat;
        if (lon < lonMin) lonMin = lon;
        if (lon > lonMax) lonMax = lon;
        PosDataType pd;
        BusInfo bi;
        pd.insert("bearing",posMap["bearing"].toDouble());
        bi.setBearing(posMap["bearing"].toDouble());
        pd.insert("lat",lat);
        pd.insert("lon",lon);
        bi.setLat(lat);
        bi.setLon(lon);
        pd.insert("speed",posMap["speed"].toDouble());
        bi.setSpeed(posMap["speed"].toDouble());
//        qDebug() << "\nvehicle\n" << vehicleMap["position"] << "\n\t route]n" << vehicleMap["trip"];
        QVariantMap tripMap = vehicleMap["trip"].toMap();
//        qDebug() << "\n\t\ttrip " << "route" <<tripMap["route_id"] << "trip" << tripMap["trip_id"];
        pd.insert("trip_id",tripMap["trip_id"].toString());
        bi.setTrip(tripMap["trip_id"].toString());
        QString route = tripMap["route_id"].toString();
        bi.setRoute(route);
        m_posMap.insertMulti(route,pd);
        m_positions.insertMulti(Pos(lat,lon), route);
        m_busPositions->addBus(bi);
        ++e;
    }

}

void source::gotPosReply()
{
    reportc(Q_FUNC_INFO);
    setReqCount(m_reqCount+1);
    QByteArray theData = posReply->readAll();
    m_posData = theData;
    pickApartPos(theData);\
//   std::cout << "Position data ----------------------------------------------------\n" << theData.data() << std::endl;

    qDebug() << "Pos Data current";
    for (auto it=m_posMap.begin(); it!= m_posMap.end(); ++it) {
        qDebug() << it.key();
        qDebug() << it.value();
    }
    qDebug() << " lat from " << latMin << " to " << latMax;
    qDebug() << " lon from " << lonMin << " to " << lonMax;
    m_busPositions->setLatMin(latMin);
    m_busPositions->setLonMin(lonMin);
    m_busPositions->signalDataChanged();
   reportqs(QString ("finished %1").arg(Q_FUNC_INFO ));
}

void source::gotSchedReply()
{
    reportc(Q_FUNC_INFO);
    setReqCount(m_reqCount+1);
    QByteArray theData = schedReply->readAll();
    m_schedData = theData;
//    pickApart(theData);
    reportqs(QString ("finished %1").arg(Q_FUNC_INFO ));
}

void source::gotStaticReply()
{
    reportc(Q_FUNC_INFO);
    setReqCount(m_reqCount+1);
    QByteArray theData = staticReply->readAll();
    m_staticData = theData;
//    pickApart(theData);
    reportqs(QString ("finished %1").arg(Q_FUNC_INFO ));
}

void source::setSourceString(QString sourceString)
{
    if (m_sourceString == sourceString)
        return;

    m_sourceString = sourceString;
    emit sourceStringChanged(sourceString);
}

void source::setReqCount(int reqCount)
{
    if (m_reqCount == reqCount)
        return;

    m_reqCount = reqCount;
    emit reqCountChanged(reqCount);
}
