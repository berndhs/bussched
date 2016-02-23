#include "source.h"
#include <QDebug>
#include <QUrl>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariant>
#include <QVariantMap>
#include <QStringList>
#include <QByteArray>
#include <QList>
#include <iostream>

void reportc (const char* s)
{
      qDebug() << s;
}
void reportss (std::string s)
{
      qDebug() << s.c_str() ;
}
void reportqs (QString s)
{
      qDebug() << s;
}
void report (int i)
{
      qDebug() << i ;
}
void report (QStringList sl)
{
    qDebug() << sl ;
}
void reportba (QByteArray ba)
{
    qDebug() << ba.length() << " bytes " << ba ;
}

source::source(QObject *parent) : QObject(parent),
    positionReq(QUrl("http://api.octa.net/gtfsrealtime/protobuf/servicealerts.aspx?format=json")),
    scheduleReq(QUrl("http://api.octa.net/gtfsrealtime/protobuf/tripupdates.aspx?format=json")),
    staticReq(QUrl("http://api.octa.net/gtfsrealtime/protobuf/servicealerts.aspx?format=json"))
{
    reportc(Q_FUNC_INFO);

}

void source::askPositions()
{
    posReply = qnam.get (positionReq);
    connect(posReply,SIGNAL(finished()),this,SLOT(gotPosReply()));
}

void source::gotPosReply()
{
   reportc(Q_FUNC_INFO);
   QByteArray theData = posReply->readAll();
   QJsonDocument doc = QJsonDocument::fromJson(theData);
   qDebug() << "doc is " << doc;
   QJsonObject obj = doc.object();
   QVariantMap var = obj.toVariantMap();
   QList<QString> keys= var.keys();
   report (var.size());
   for (auto elt = keys.begin(); elt != keys.end(); ++ elt) {
       std::cout << elt->toStdString() << std::endl;
   }
   QVariant header = var["header"];
   QJsonArray data = var["entity"].toJsonArray();
   reportqs (header.toString());
   reportqs (QString("number of entities: %1").arg(data.size()));
//   reportc ("\n\n\tbyte array\n");
//   reportba (theData);
   reportqs(QString ("finished %1").arg(Q_FUNC_INFO ));
}
