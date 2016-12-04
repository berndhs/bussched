#ifndef UTIL_H
#define UTIL_H

#include <QDebug>


class Util
{
public:
    Util();
    double xPos (double lon);
    double yPos (double lat);

    void setLon (double min, double max) { lonMin = min; lonMax = max; lonRange = max-min; }
    void setLat (double min, double max) { latMin = min; latMax = max; latRange = max-min; }
    void setX (int min, int max) { xmin = min; xmax = max; }
    void setY (int min, int max) { ymin = min; ymax = max; }

    double lastX() { return lastXval; }
    double lastY() { return lastYval; }
    double lastLon() { return lastLonVal; }
    double lastLat() { return lastLatVal; }

private:

    double stretchX(double xFrac);
    double stretchY(double yFrac);

    double lonMax;
    double lonMin;
    double lonRange;
    double latMax;
    double latMin;
    double latRange;
    int xmin;
    int xmax;
    int ymin;
    int ymax;

    double lastXval;
    double lastYval;

    double lastLonVal;
    double lastLatVal;


};

#endif // UTIL_H
