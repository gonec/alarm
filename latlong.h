#ifndef LATLONG_H
#define LATLONG_H
#include <QString>

struct LatLong
{
public:
    LatLong();
    // Доли минуты
    unsigned dm             : 14;
    // Минуты
    unsigned minuts         : 6;
    // Градуcы
    unsigned deg            : 8;
    // Полушарие серверное 0, южное 1
    unsigned hemisphere     : 1;
    // Признак широты 0, долготы 1
    unsigned isLongtitude            : 1;
    // Константа всегда 01
    unsigned c              : 2;
    QString show();
    QString showMachine();
    //перевод из deg- целое число градусов,
    //minuts - целое число минут
    //dm - дробное число минут в
    //десятичную дробь представляющую из себя градусы
    float calculateDegrees( int deg, int minuts, int dm) ;
};

#endif // LATLONG_H
