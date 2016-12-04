#ifndef SOURCE_H
#define SOURCE_H


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



#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QPair>
#include <QMap>
#include <QMultiMap>
#include <QVariant>
#include <QSet>

#include "makesvg.h"
#include "buspositions.h"
#include "util.h"

class source : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString sourceString READ sourceString WRITE setSourceString NOTIFY sourceStringChanged)
    Q_PROPERTY(int reqCount READ reqCount WRITE setReqCount NOTIFY reqCountChanged)
    Q_PROPERTY(BusPositions* busPositions READ busPositions)
    Q_PROPERTY(int busCount READ busCount NOTIFY busCountChanged)


public:
    explicit source(QObject *parent = 0);

    Q_INVOKABLE void askPositions();
    Q_INVOKABLE void getFormattedString (QString s);
    Q_INVOKABLE void printData();
    Q_INVOKABLE void setXY(double xMin, double xMax, double yMin, double yMax);
    Q_INVOKABLE void updateMap();
    Q_INVOKABLE void stop();

    int addStation (double lat, double lon, QString name);



    QString sourceString() const;

    int reqCount() const;

    BusPositions * busPositions()
    {
        return m_busPositions;
    }

    int busCount() const
    {
        return m_busPositions->rowCount();
    }

signals:


    void sourceStringChanged(QString sourceString);

    void reqCountChanged(int reqCount);
    void newMap (QString mapName);

    void busCountChanged(int busCount);

public slots:

    void gotPosReply();
    void gotSchedReply();
    void gotStaticReply();

    void setSourceString(QString sourceString);

    void setReqCount(int reqCount);

private:

    void loadStations();

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

    QSet <QString> usefulRoutes;

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
    Util util;
    int m_busCount;

    int m_stations;
};



#endif // SOURCE_H
