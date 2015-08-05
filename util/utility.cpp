#include "utility.h"
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QDebug>
#include <QApplication>


Utility::Utility()
{
}

QJsonObject Utility::getJSONFromFile(const QString &filePath)
{
    QFile file(filePath);
    QString jsonStr = "";
    if (file.open(QFile::ReadOnly)) {
        jsonStr = file.readAll();
        file.close();
    }
    else {
        qDebug() <<  QObject::tr("Failed to open '%1'").arg(filePath) << endl;
    }

    QJsonObject json;
    QJsonParseError jerror;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8(), &jerror);
    if (jerror.error != QJsonParseError::NoError) {
        qDebug() << jerror.errorString() << endl;
        return json;
    }
    json = jsonDoc.object();

    return json;
}

QJsonObject Utility::getJSONFromString(const QString &jsonStr)
{
    QJsonObject json;
    QJsonParseError jerror;
    qDebug() << jsonStr;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonStr.toUtf8(), &jerror);
    if (jerror.error != QJsonParseError::NoError) {
        qDebug() << jerror.errorString() << endl;
        return json;
    }
    json = jsonDoc.object();

    return json;
}

void Utility::loadStyle(const QString& filePath){
    QFile file(filePath);
    if (file.open(QFile::ReadOnly)) {
        qDebug() << QObject::tr("Style file %1 opened").arg(filePath) << endl;
        QString styleSheet = QString(file.readAll());
        qApp->setStyleSheet(styleSheet);
        file.close();
    }

}
