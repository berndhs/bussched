#ifndef BUSPOSITIONS_H
#define BUSPOSITIONS_H


#include <QAbstractItemModel>
#include <QVariant>
#include <QMap>
#include <QByteArray>
#include <QHash>
#include <QObject>

#include "businfo.h"



class BusPositions : public QAbstractItemModel
{
    Q_OBJECT

public:

    BusPositions (QObject * parent=0);
    ~BusPositions();

    int rowCount() const;
    Q_INVOKABLE double xPos(int row) const;
    Q_INVOKABLE double yPos(int row) const;
    Q_INVOKABLE QString route(int row) const;
    Q_INVOKABLE double bearing(int row) const;
    Q_INVOKABLE double lat(int row) const;
    Q_INVOKABLE double lon(int row) const;
    Q_INVOKABLE QString trip(int row) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

    void addBus(BusInfo bi);

    void setLatMin (double lm) { latMin = lm; }
    void setLonMin (double lm) { lonMin = lm; }
    void setScaleLat(double value) { scaleLat = value; }
    void setScaleLon(double value) { scaleLon = value; }

    void signalDataChanged();


    enum BusRoles {
        TooSmall = Qt::UserRole+1,
        XPOS,
        YPOS,
        Lat,
        Lon,
        BusRoute,
        Bearing,
        Speed,
        Trip,
        TooBig
    };


private:

    int maxRow;
    double latMin;
    double lonMin;
    double scaleLat;
    double scaleLon;

    double scaleX (double lon) const;
    double scaleY (double lat) const;

    QList<BusInfo> m_busList;

    QObject *m_parent;



    double xMin;
    double yMin;
    double xRange;
    double yRange;
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex & index) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    void setXY (double xMn, double xRnge, double yMn, double yRnge);
};

#endif // BUSPOSITIONS_H
