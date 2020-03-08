#include <QStringList>
#include <QString>

#include "convert.h"

qint32 convertRealToInt(qreal r)
{
    return r < 0.0 ? (qint32)qCeil(r) :
                     (qint32)qFloor(r);
}

QString lat2rus(QString latStr)
{
    QString rusStr(latStr);

    int len = latStr.length();
    for (int i = 0; i < len; i++) {
        QChar latChar = latStr.at(i);
        if (latChar == 'A') {
            QChar rusChar = QString::fromLocal8Bit("А")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'B') {
            QChar rusChar = QString::fromLocal8Bit("Б")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'C') {
            QChar rusChar = QString::fromLocal8Bit("Ц")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'D') {
            QChar rusChar = QString::fromLocal8Bit("Д")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'E') {
            QChar rusChar = QString::fromLocal8Bit("Е")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'F') {
            QChar rusChar = QString::fromLocal8Bit("Ф")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'G') {
            QChar rusChar = QString::fromLocal8Bit("Г")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'H') {
            QChar rusChar = QString::fromLocal8Bit("Х")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'I') {
            QChar rusChar = QString::fromLocal8Bit("И")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'J') {
            QChar rusChar = QString::fromLocal8Bit("Й")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'K') {
            QChar rusChar = QString::fromLocal8Bit("К")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'L') {
            QChar rusChar = QString::fromLocal8Bit("Л")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'M') {
            QChar rusChar = QString::fromLocal8Bit("М")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'N') {
            QChar rusChar = QString::fromLocal8Bit("Н")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'O') {
            QChar rusChar = QString::fromLocal8Bit("О")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'P') {
            QChar rusChar = QString::fromLocal8Bit("П")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'Q') {
            QChar rusChar = QString::fromLocal8Bit("Щ")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'R') {
            QChar rusChar = QString::fromLocal8Bit("Р")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'S') {
            QChar rusChar = QString::fromLocal8Bit("С")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'T') {
            QChar rusChar = QString::fromLocal8Bit("Т")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'U') {
            QChar rusChar = QString::fromLocal8Bit("У")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'V') {
            QChar rusChar = QString::fromLocal8Bit("Ж")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'W') {
            QChar rusChar = QString::fromLocal8Bit("В")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'X') {
            QChar rusChar = QString::fromLocal8Bit("Ь")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'Y') {
            QChar rusChar = QString::fromLocal8Bit("Ы")[0];
            rusStr[i] = rusChar;
        } else if (latChar == 'Z') {
            QChar rusChar = QString::fromLocal8Bit("З")[0];
            rusStr[i] = rusChar;
        }
    }

    return rusStr;
}

#include <QDebug>
QString coordRaw2readable(QString coordRaw)
{
    if (coordRaw.isEmpty())
        return QString();

    QStringList coord = coordRaw.split(" ");

//    qDebug() << "1. " << coord;

    QString lat_gg = coord.at(0);
    if (lat_gg.length() == 1)
        lat_gg.prepend("0");
    QString lat_mm = coord.at(1);
    if (lat_mm.length() == 1)
        lat_mm.prepend("0");
    QString lat_ss = coord.at(2);
    if (lat_ss.length() == 5)
        lat_ss.prepend("0");

    QString lon_gg = coord.at(3);
    if (lon_gg.length() == 1)
        lon_gg.prepend("0");
    if (lon_gg.length() == 2)
        lon_gg.prepend("0");
    QString lon_mm = coord.at(4);
    if (lon_mm.length() == 1)
        lon_mm.prepend("0");
    QString lon_ss = coord.at(5);
    if (lon_ss.length() == 5)
        lon_ss.prepend("0");

    return QString(lat_gg + "° " + lat_mm + "\' " + lat_ss + "\"" + "   " +
                   lon_gg + "° " + lon_mm + "\' " + lon_ss + "\"");
}
