#include "source.h"
#include <QDebug>
#include <QUrl>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
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

QString escape (QString s)
{
    return "\"" + s + "\"";
}

QByteArray unescape (QByteArray b)
{
    QByteArray res;
    for (int i=0; i<b.length(); ++i) {
        if (b[i] != '\\') {
            res.append(b[i]);
        } else {
            if (b[i+1] == '\"') {
                res.append('"');
            } else {
                res.append("\"");
                res.append(b[i+1]);
                i += 1;
            }
        }
    }
    return res;
}



source::source(QObject *parent) : QObject(parent),
    positionReq(QUrl("http://api.octa.net/gtfsrealtime/protobuf/servicealerts.aspx?format=json")),
    scheduleReq(QUrl("http://api.octa.net/gtfsrealtime/protobuf/tripupdates.aspx?format=json")),
    staticReq(QUrl("http://api.octa.net/gtfsrealtime/protobuf/servicealerts.aspx?format=json")),
    m_reqCount(0)
{
    reportc(Q_FUNC_INFO);

}

void source::askPositions()
{
    posReply = qnam.get (positionReq);
    connect(posReply,SIGNAL(finished()),this,SLOT(gotPosReply()));
    schedReply = qnam.get (scheduleReq);
    connect(schedReply,SIGNAL(finished()),this,SLOT(gotSchedReply()));
    staticReply = qnam.get (staticReq);
    connect(staticReply,SIGNAL(finished()),this,SLOT(gotStaticReply()));
}

void source::getFormattedString(QString s)
{
    qDebug() << "string \n" << s;
}

void source::printData()
{

    qDebug() << Q_FUNC_INFO;
    qDebug () << " all the same " << ((m_posData == m_schedData) && (m_posData == m_staticData));
}

QString source::sourceString() const
{
    return m_sourceString;
}

int source::reqCount() const
{
    return m_reqCount;
}

void pickApart (QByteArray theData)
{
    qDebug() << Q_FUNC_INFO ;
    QJsonDocument doc = QJsonDocument::fromJson(theData);
    QJsonObject obj = doc.object();
    QJsonValue head = obj["header"];
    qDebug() << "header";
    qDebug() << "is object " << head.isObject();
    qDebug() << "is undefined " << head.isUndefined();
    qDebug() << "is null " << head.isNull();
    qDebug() << "is array " << head.isArray();
    QJsonValue entity = obj["entity"];
    qDebug() << "entity";
    qDebug() << "is object " << entity.isObject();
    qDebug() << "is undefined " << entity.isUndefined();
    qDebug() << "is null " << entity.isNull();
    qDebug() << "is array " << entity.isArray();
    QJsonArray enArray = entity.toArray();
    qDebug () << "enArray count " << enArray.count();
    int e(0);
    for (auto elt=enArray.begin(); elt != enArray.end(); ++ elt, ++e) {
        QVariant var = elt->toVariant();
        qDebug() << "element " << e << " ::::::::::::: " << var;
    }

}

void source::gotPosReply()
{
    reportc(Q_FUNC_INFO);
    setReqCount(m_reqCount+1);
    QByteArray theData = posReply->readAll();
    m_posData = theData;
    pickApart(theData);\
//   std::cout << "Position data ----------------------------------------------------\n" << theData.data() << std::endl;

   reportqs(QString ("finished %1").arg(Q_FUNC_INFO ));
}

void source::gotSchedReply()
{
    reportc(Q_FUNC_INFO);
    setReqCount(m_reqCount+1);
    QByteArray theData = schedReply->readAll();
    m_schedData = theData;
//    pickApart(theData);
    reportqs(QString ("finished %1").arg(Q_FUNC_INFO ));
}

void source::gotStaticReply()
{
    reportc(Q_FUNC_INFO);
    setReqCount(m_reqCount+1);
    QByteArray theData = staticReply->readAll();
    m_staticData = theData;
//    pickApart(theData);
    reportqs(QString ("finished %1").arg(Q_FUNC_INFO ));
}

void source::setSourceString(QString sourceString)
{
    if (m_sourceString == sourceString)
        return;

    m_sourceString = sourceString;
    emit sourceStringChanged(sourceString);
}

void source::setReqCount(int reqCount)
{
    if (m_reqCount == reqCount)
        return;

    m_reqCount = reqCount;
    emit reqCountChanged(reqCount);
}
