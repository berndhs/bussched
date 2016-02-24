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
    m_reqCount(0)
{
    reportc(Q_FUNC_INFO);

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
        PosDataType pd;
        pd.insert("bearing",posMap["bearing"].toDouble());
        pd.insert("lat",posMap["latitude"].toDouble());
        qDebug () << "lat" << posMap["latitude"];
        pd.insert("lon",posMap["longitude"].toDouble());
        pd.insert("speed",posMap["speed"].toDouble());
//        qDebug() << "\nvehicle\n" << vehicleMap["position"] << "\n\t route]n" << vehicleMap["trip"];
        QVariantMap tripMap = vehicleMap["trip"].toMap();
//        qDebug() << "\n\t\ttrip " << "route" <<tripMap["route_id"] << "trip" << tripMap["trip_id"];
        pd.insert("trip_id",tripMap["trip_id"].toString());
        m_posMap.insertMulti(tripMap["route_id"].toString(),pd);
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
