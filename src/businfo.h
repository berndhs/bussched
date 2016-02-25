#ifndef BUSINFO_H
#define BUSINFO_H

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
