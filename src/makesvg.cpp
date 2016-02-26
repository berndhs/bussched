#include "makesvg.h"
#include <QDir>
#include <QDebug>
#include <QTemporaryFile>

MakeSVG::MakeSVG()
{

}

int MakeSVG::startFile(QString filePattern, int width, int height)
{
    QString tmpTemplate (QString("%1/%2")
                      .arg (QDir::tempPath())
                      .arg (filePattern));
    qDebug() << Q_FUNC_INFO << "temp files pattern " << tmpTemplate;
    QTemporaryFile *newMap = new QTemporaryFile (tmpTemplate);
    newMap->open();
    int newHandle = m_files.count();
    m_files[newHandle] = newMap;
    qDebug() << Q_FUNC_INFO << "temp file pointer " << newMap;
    writeSvgHead(newMap, width, height);
    qDebug() << "file will be " << newMap->fileName();
    return newHandle;
}

QString MakeSVG::closeFile(int handle)
{
    QString name;
    QFile *fp = m_files[handle];
    if (fp) {
        writeSvgTail(fp);
        name = fp->fileName();
        fp->close();
        m_files[handle] = 0;
    }
    return name;
}

void MakeSVG::addCross(int handle, double x, double y, double armLen, int width)
{
    QFile * fp= m_files[handle];
    if (fp) {
        if (!fp->isOpen()) {
            fp->open(QFile::WriteOnly);
            if (!fp->isOpen()) {
                return;
            }
        }
        QByteArray cross = svgCross(x,y,armLen,width).toLatin1();
        int  bytes = fp->write(cross);
        qDebug () << " wrote " << bytes << " as " << cross;
    }
}

void
MakeSVG::writeSvgHead (QIODevice * device, int width, int height)
{
    if (!device) {
        return;
    }
    device->write (QString("<?xml version=\"1.0\" standalone=\"no\"?>\n"
                   "<svg width=\"%1\" height=\"%2\" >\n").arg(width).arg(height).toLatin1());
}

void
MakeSVG::writeSvgTail (QIODevice * device)
{
    if (!device) {
        return;
    }
    device->write ("\n</svg>\n");
}

QString
MakeSVG::svgCross(double x, double y, double armLen, int width)
{
    QString svg;
    QString style (QString(" style=\"stroke: rgb(255,0,0);stroke-width:%1\"").arg(width));
    svg.append (QString("<line x1=\"%1\" y1=\"%2\" x2=\"%3\" y2=\"%4\" ").arg(x).arg(y-armLen).arg(x).arg(y+armLen));
    svg.append (style);
    svg.append("/>\n");
    svg.append (QString("<line x1=\"%1\" y1=\"%2\" x2=\"%3\" y2=\"%4\" ").arg(x-armLen).arg(y).arg(x+armLen).arg(y));
    svg.append (style);
    svg.append("/>\n");
    return svg;
}


//int
//MakeSVG::mappedLon (qreal rawLon)
//{
//    if (rangeLon < 0.00001) {
//        return 1;
//    }
//    return qRound (1000.0 * lonScale * (rawLon - minLon) / rangeLon);
//}

//int
//MakeSVG::mappedLat (qreal rawLat)
//{
//    if (rangeLat < 0.00001) {
//        return 1;
//    }
//    return 1000 - qRound (1000.0 * latScale * (rawLat - minLat) / rangeLat);
//}
