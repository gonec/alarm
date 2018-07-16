#ifndef TIMESTRUCT_H
#define TIMESTRUCT_H
#include <QDebug>
#include <QDate>
#include <QTime>
struct TimeStruct
{
public:
    TimeStruct();
    // секунды
    unsigned seconds    : 6;
    // минуты
    unsigned minuts     : 6;
    // часы
    unsigned hours      : 5;
    // дни
    unsigned day        : 5;
    // месяцы
    unsigned month      : 4;
    // год
    unsigned year       : 6;
    void show();
    bool operator ==(TimeStruct );
    QDate getDate();
    QTime getTime();
    QDate mDate;
    QTime mTime;
    QDateTime datetime() const ;
};

#endif // TIMESTRUCT_H
