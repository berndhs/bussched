#include "util.h"
#include <QDebug>

Util::Util()
  :lonMax(-117.589),
    lonMin(-118.41),
    latMin(33.4),
    latMax(33.8)
{
  latRange = qAbs(latMax - latMin);
  lonRange = qAbs(lonMax - lonMin);
  qDebug() << Q_FUNC_INFO << "x min" << lonMin << "to " << lonMax
           << "y " << latMin << "to" << latMax
           << "ranges " << latRange << " and " << lonRange;
  qDebug() << "----------------------";
}

double Util::xPos(double lon)
{
  double lonSpot = (qAbs(lon) - qAbs(lonMin));
  double lonFrac = lonSpot/lonRange;
  double xd = stretchX(lonFrac);
  qDebug() << Q_FUNC_INFO << "lon" << lon << "spot" << lonSpot << "frac" << lonFrac << "xdis" << xd;
  lastXval = xd;
  lastLonVal = lon;
  return qAbs(xd); // invert x: left is 0, right is most pos
}

double Util::yPos(double lat)
{
  double latSpot = (lat - latMin);
  double latFrac = latSpot/latRange;
  double yd = stretchY(latFrac);
  qDebug() << Q_FUNC_INFO << "lat" << lat << "spot" << latSpot
           << "frac" << latFrac << "range" << latRange << "ydis " << yd;
  lastYval = yd;
  lastLatVal = lat;
  return  qAbs(yd);
}

double Util::stretchX(double xFrac)
{
  return double(xmin) + xFrac * (double(xmax) - double(xmin));
}

double Util::stretchY(double yFrac)
{
  return double(ymin) + yFrac * (double(ymax) - double(ymin));
}
