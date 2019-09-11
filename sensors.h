#ifndef SENSORS_H
#define SENSORS_H
#include <QDebug>
#include <QMap>
#include <iostream>
struct Sensors
{
public:
    Sensors();
    // rN - резерв
    // alarm тревожная кнопка
    unsigned a              : 10;  // 0
    unsigned b              : 10;  // 10
    unsigned IG             : 1;  // 20
    unsigned AL             : 1;  // 21
    unsigned D3             : 1;  // 22
    unsigned D2             : 1;  // 23
    unsigned D1             : 1;  // 24
    unsigned r26            : 1;  // 25
    unsigned r27            : 1;  // 26
    unsigned EC             : 1;  // 27
    unsigned r29            : 1;
    unsigned r30            : 1;  // 28
    unsigned r31            : 1;  // 29
    unsigned r32            : 2;  // 30
    void show();
private:
   // QMap<QString, int> mSens;
};

#endif // SENSORS_H
