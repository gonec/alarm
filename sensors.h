#ifndef SENSORS_H
#define SENSORS_H
#include <QDebug.h>
#include <QMap.h>
#include <iostream>
struct Sensors
{
public:
    Sensors();
    // rN - резерв
    // alarm тревожная кнопка
    unsigned a0             : 1;  // 0
    unsigned a1             : 1;  // 1
    unsigned a2             : 1;  // 2
    unsigned a3             : 1;  // 3
    unsigned a4             : 1;  // 4
    unsigned a5             : 1;  // 5
    unsigned a6             : 1;  // 6
    unsigned a7             : 1;  // 7
    unsigned a8             : 1;  // 8
    unsigned a9            : 1;  // 9
    unsigned b0            : 1;  // 10
    unsigned b1            : 1;  // 11
    unsigned b2            : 1;  // 12
    unsigned b3            : 1;  // 13
    unsigned b4            : 1;  // 14
    unsigned b5            : 1;  // 15
    unsigned b6            : 1;  // 16
    unsigned b7            : 1;  // 17
    unsigned b8            : 1;  // 18
    unsigned b9            : 1;  // 19
    unsigned IG             : 1;  // 20
    unsigned AL             : 1;  // 21
    unsigned D3             : 1;  // 22
    unsigned D2             : 1;  // 23
    unsigned D1             : 1;  // 24
    unsigned r26            : 1;  // 25
    unsigned r27            : 1;  // 26
    unsigned EC            : 1;  // 27
    unsigned r29           : 1;
    unsigned r30            : 1;  // 28
    unsigned r31            : 1;  // 29
    unsigned r32            : 2;  // 30
    void show();
private:
   // QMap<QString, int> mSens;
};

#endif // SENSORS_H
