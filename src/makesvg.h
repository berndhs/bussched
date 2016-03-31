#ifndef MAKESVG_H
#define MAKESVG_H


/****************************************************************
 * This file is distributed under the following license:
 *
 * Copyright (C) 2016, Bernd Stramm
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA  02110-1301, USA.
 ****************************************************************/


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

    void addCross (int handle, double x, double y, double armLen, int width=1, QString color= "#ff0000");

private:

    void writeSvgHead (QIODevice * device, int width, int height);
    void writeSvgTail (QIODevice * device);
    QString svgCross (double x, double y, double armLen, int width, QString color="#ff0000");
//    int  mappedLon (qreal rawLon);
//    int  mappedLat (qreal rawLat);

    QMap<int, QFile*> m_files;
};

#endif // MAKESVG_H
