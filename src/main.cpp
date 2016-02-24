#include <QApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QString>
#include <QDebug>
#include <QMessageLogContext>
#include "source.h"

#include <stdio.h>
#include <stdlib.h>

//void myDebug (QtMsgType type, const QMessageLogContext & context, const QString & msg)
//{
//    fprintf (stderr, ("severity %d msg %s\n",type,msg.toStdString().c_str()));
//    fflush (stderr);
//}

int main(int argc, char *argv[])
{

    qDebug() << Q_FUNC_INFO << "starting";
//    qInstallMessageHandler(myDebug);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<source>("com.berndhs",1,0,"Source");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    int done = app.exec();
    qDebug () << Q_FUNC_INFO << "all done" << done;
}
