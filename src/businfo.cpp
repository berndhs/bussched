#include "businfo.h"
#include <QDebug>

BusInfo::BusInfo()
    : lat(0), lon(0), bearing(0), speed(0), route("NoRoute"), trip("NoTrip")
{
}

BusInfo::BusInfo(double la, double lo, double be, double sp, QString ro, QString tr):
    lat(la), lon(lo), bearing(be), speed (sp), route(ro), trip(tr)
{

}
