#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QString>
#include <QDebug>
#include <QMessageLogContext>
#include "source.h"
#include "buspositions.h"

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{

    qDebug() << Q_FUNC_INFO << "starting";
    QGuiApplication app(argc, argv);
    source theSource;
    theSource.askPositions();
    BusPositions * theBuses = theSource.busPositions();

    QQmlApplicationEngine engine;
    qmlRegisterType<source>("com.berndhs",1,0,"Source");
    qmlRegisterType<BusPositions>("com.berndhs",1,0,"BusPositions");
    auto context = engine.rootContext();
    context->setContextProperty("theSource",&theSource);
    context->setContextProperty("buses",theBuses);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    int done = app.exec();
    qDebug () << Q_FUNC_INFO << "all done" << done;
}
