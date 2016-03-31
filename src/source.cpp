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
#include <cmath>


/****************************************************************
 * This file is distributed under the following license:
 *
 * Copyright (C) 2016, Bernd Stramm
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA  02110-1301, USA.
 ****************************************************************/


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
    usefulRoutes << "1" << "177" << "89";
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
    long double latDiff = latMax - latMin;
    long double lonDiff = lonMax - lonMin;
    long double latRange = latDiff < 0 ? -latDiff : latDiff;
    long double lonRange = lonDiff < 0 ? -lonDiff : lonDiff;
    long double xRange = abs(xMax - xMin);
    this->xRange = xRange;
    long double yRange = abs(yMax - yMin);
    this->yRange = yRange;
    long double latScale = yRange / latRange;
    long double lonScale = xRange / lonRange;
    m_busPositions->setScaleLat(latScale);
    m_busPositions->setScaleLon(lonScale);
    m_busPositions->signalDataChanged();
    m_busPositions->setXY (xMin,xRange, xMin, yRange);
}

void source::updateMap()
{
    qDebug() << Q_FUNC_INFO;
    int handle = m_fileMaker.startFile("map_img_XXXXXX.svg",int(ceil(xRange)),int(ceil(yRange)));
    qDebug() << " file handle " << handle;
    // write the stuff into the file
    for (int r=0;r<m_busPositions->rowCount();++r) {
        QString rt = m_busPositions->route(r);
        QString col = (rt == "89" ? "#ffffff" : ( rt = "1" ? "#00ff00" : (rt == "177" ? "#0000ff" : "ff0000")));
        if (rt == "177") {
            col = "#00ffff";
            qDebug() <<  177 << "at " << m_busPositions->xPos(r),m_busPositions->yPos(r);
            Q_ASSERT (false);
        }

        m_fileMaker.addCross(handle,m_busPositions->xPos(r),m_busPositions->yPos(r), 5, 1, col);
    }
    QString name = m_fileMaker.closeFile(handle);
    emit newMap(name);
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
        if (usefulRoutes.contains(route)) {
            m_posMap.insertMulti(route,pd);
            m_positions.insertMulti(Pos(lat,lon), route);
            m_busPositions->addBus(bi);
        }
        ++e;
    }

}

void source::gotPosReply()
{
    reportc(Q_FUNC_INFO);
    setReqCount(m_reqCount+1);
    QByteArray theData = posReply->readAll();
    m_posData = theData;
    m_posMap.clear();
    m_positions.clear();
    pickApartPos(theData);\
    //   std::cout << "Position data ----------------------------------------------------\n" << theData.data() << std::endl;

    qDebug() << "Pos Data current";
    //    for (auto it=m_posMap.begin(); it!= m_posMap.end(); ++it) {
    //        qDebug() << it.key();
    //        qDebug() << it.value();
    //    }
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
