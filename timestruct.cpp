#include "timestruct.h"

TimeStruct::TimeStruct()
{

}

void TimeStruct::show(){
    mDate.setDate(2000+year, month, day);
    mTime = QTime(hours, minuts, seconds);
    //qDebug()<<mDate.toString()<<" "<<mTime.toString();
    //qDebug() << "Seconds:"  << seconds;
    //qDebug() << "Minuts:"   << minuts;
    //qDebug() << "Hours:"    << hours;
    //qDebug() << "Days:"     << day;
    //qDebug() << "Month:"    << month;
    //qDebug() << "Years:"    << year;
}

QDate TimeStruct::getDate(){
   mDate.setDate(2000 + year, month, day);
   return mDate;
}

QTime TimeStruct::getTime(){
     mTime = QTime(hours, minuts, seconds);
     return mTime;
}

QDateTime TimeStruct::datetime() const {
    QDate dt = QDate(2000 + year, month, day);
    QTime tm = QTime(hours, minuts, seconds);
    return QDateTime(dt, tm);
}
bool TimeStruct::operator ==(TimeStruct rhs){

    if ( seconds == rhs.seconds  &&
         minuts  == rhs.minuts &&
         day     == rhs.day &&
         month   == rhs.month &&
         year    == rhs.year
    ){
        return true;
    }
    return false;

}
