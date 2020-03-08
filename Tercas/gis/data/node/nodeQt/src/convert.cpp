#include "convert.h"

QString GGGtoGGMMSS(double ggg)
{
    int gg = (int)ggg;
    int mm = (int)((ggg - gg) * 60.0);
    double ss = (ggg - gg) * 60.0 * 60.0 - mm * 60.0;

    return QString("%1 %2 %3")
        .arg(gg)
        .arg(mm)
        .arg(ss);
}
