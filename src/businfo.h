#ifndef BUSINFO_H
#define BUSINFO_H


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



#include <QString>


class BusInfo
{
public:
    BusInfo();
    BusInfo(double la, double lp, double be, double sp, QString ro, QString tr);
    double Lat() const { return lat; }
    double Lon() const { return lon; }
    double Bearing() const { return bearing; }
    double Speed() const { return speed; }

    QString Route() const { return route; }
    QString Trip() const { return trip; }

    void setLat(double l) { lat=l; }
    void setLon(double l) { lon=l; }
    void setBearing(double b) { bearing = b; }
    void setSpeed (double s) { speed = s; }
    void setRoute(QString r) { route = r; }
    void setTrip (QString t) { trip = t; }


private:

    double lat;
    double lon;
    double bearing;
    double speed;
    QString route;
    QString trip;
};

#endif // BUSINFO_H
