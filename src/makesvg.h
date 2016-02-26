#ifndef MAKESVG_H
#define MAKESVG_H

// Make SVG files

#include <QIODevice>
#include <QFile>
#include <QString>
#include <QMap>
#include <QPair>


class MakeSVG
{
public:
    MakeSVG();

    int startFile(QString filePattern,int width, int height);
    QString closeFile (int handle); // return file name

    void addCross (int handle, double x, double y, double armLen, int width=1);

private:

    void writeSvgHead (QIODevice * device, int width, int height);
    void writeSvgTail (QIODevice * device);
    QString svgCross (double x, double y, double armLen, int width);
//    int  mappedLon (qreal rawLon);
//    int  mappedLat (qreal rawLat);

    QMap<int, QFile*> m_files;
};

#endif // MAKESVG_H
