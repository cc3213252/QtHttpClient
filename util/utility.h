#ifndef UTILITY_H
#define UTILITY_H

#include <QString>
#include <QFile>
#include <QDebug>

class Utility
{
public:
    Utility();
    static QJsonObject getJSONFromFile(const QString &filePath);
    static void loadStyle(const QString& filePath);
    static QJsonObject getJSONFromString(const QString &jsonStr);
};

#endif // UTILITY_H
