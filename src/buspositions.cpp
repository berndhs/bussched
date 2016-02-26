#include "buspositions.h"
#include <QDebug>

BusPositions::BusPositions(QObject *parent)
    :QAbstractItemModel(parent)
{
    m_parent = parent;
}

BusPositions::~BusPositions()
{
    qDebug() << Q_FUNC_INFO;
}

int BusPositions::rowCount() const
{
    return m_busList.count();

}

double BusPositions::xPos(int row) const
{
    double xd = scaleX(m_busList[row].Lon());
    qDebug() << Q_FUNC_INFO << "row " << row << "lon" << m_busList[row].Lon() << "xd" << xd;
    return xd;
}

double BusPositions::yPos(int row) const
{
    double yd = scaleY(m_busList[row].Lat());
    return yd;
}

QString BusPositions::route(int row) const
{
    QString rt = m_busList[row].Route();
    return rt;
}

double BusPositions::bearing(int row) const
{
    double br = m_busList[row].Bearing();
    return br;
}

double BusPositions::lat(int row) const
{
    double lati = m_busList[row].Lat();
    return lati;
}

double BusPositions::lon(int row) const
{
    double longi = m_busList[row].Lon();
    return longi;
}

QString BusPositions::trip(int row) const
{
    QString tr = m_busList[row].Trip();
    return tr;
}

QVariant BusPositions::data(const QModelIndex &index, int role) const
{
    QVariant result;
    int row = index.row();
    if (row >= 0 && row < rowCount() && role > TooSmall && role < TooBig) {
        BusInfo bi = m_busList[row];
        switch (role) {
        case XPOS:
            result = scaleX(bi.Lon());
            break;
        case YPOS:
            result = scaleY(bi.Lat());
            break;
        case Lat:
            result = bi.Lat();
            break;
        case Lon:
            result = bi.Lon();
            break;
        case BusRoute:
            result = bi.Route();
            break;
        case Trip:
            result = bi.Trip();
            break;
        case Bearing:
            result = bi.Bearing();
            break;
        case Speed:
            result = bi.Speed();
            break;
        }
    }
    return result;
}

QHash<int, QByteArray> BusPositions::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(XPOS,"xPOS");
    roles.insert(YPOS,"yPOS");
    roles.insert(Lat,"lat");
    roles.insert(Lon,"lon");
    roles.insert(BusRoute,"busRoute");
    roles.insert (Trip,"trip");
    roles.insert(Bearing,"bearing");
    roles.insert(Speed,"speed");

    return roles;
}

void BusPositions::addBus(BusInfo bi)
{
    m_busList.append(bi);
}

void BusPositions::signalDataChanged()
{
    QModelIndex botLeft = BusPositions::createIndex(0,0);
    QModelIndex topRight = BusPositions::createIndex(m_busList.count()-1,0);
    emit dataChanged(botLeft,topRight);
}

double BusPositions::scaleX(double lon) const
{
    qDebug() << Q_FUNC_INFO << lon << lonMin << scaleLon;
    return (lon-lonMin) / scaleLon * xRange + xMin;
}

double BusPositions::scaleY(double lat) const
{
    return (lat-latMin) / scaleLat * yRange + yMin;
}

QModelIndex BusPositions::index(int row, int column, const QModelIndex &parent) const
{
    return BusPositions::createIndex(row,column);
}

QModelIndex BusPositions::parent(const QModelIndex &index) const
{
    return QModelIndex();
}


int BusPositions::rowCount(const QModelIndex &parent) const
{
    return m_busList.count();
}

int BusPositions::columnCount(const QModelIndex &parent) const
{
    return 1;
}

void BusPositions::setXY(double xMn, double xRnge, double yMn, double yRnge)
{
    xMin = xMn; xRange = xRnge;
    yMin = yMn; yRange = yRnge;
}

