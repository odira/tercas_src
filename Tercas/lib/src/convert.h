#ifndef CONVERT_H
#define CONVERT_H

#include <QtMath>

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE


qint32 convertRealToInt(qreal r);

/*
 *   Translate latin into russian
 */
QString lat2rus(QString latStr);

/*
 *   Convert raw coord to readable
 */
QString coordRaw2readable(QString coordRaw);

#endif // CONVERT_H
