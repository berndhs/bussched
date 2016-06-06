#ifndef UTIL_H
#define UTIL_H

#include <QDebug>


class Util
{
public:
    Util();
    double xPos (double lon) const;
    double yPos (double lat) const;

    void setLon (double min, double max) { lonMin = min; lonMax = max; lonRange = max-min; }
    void setLat (double min, double max) { latMin = min; latMax = max; latRange = max-min; }
    void setX (int min, int max) { xmin = min; xmax = max; }
    void setY (int min, int max) { ymin = min; ymax = max; }

private:

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


};

#endif // UTIL_H
