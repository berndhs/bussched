#include "util.h"

Util::Util()
{

}

double Util::xPos(double lon) const
{
    double xd = ((lon + 118.2) / 1.2) * 800;
//    double xd = scaleX(m_busList[row].Lon());
    qDebug() << Q_FUNC_INFO <<"lon" <<lon << "xd" << xd;
    return xd;
}

double Util::yPos(double lat) const
{
    double yd = ((34.5 - lat)/1.8) * 425 + 25;
    return yd;
}
