#ifndef DATARECORD_H
#define DATARECORD_H
#include <QDate>
#include "coords.h"
#include "latlong.h"
#include "sensors.h"
#include "timestruct.h"
#include "course.h"
struct DataRecord
{
public:
    DataRecord();
    DataRecord(TimeStruct, Coords, Sensors) ;
    DataRecord(TimeStruct, Coords, Sensors, Course);
    //Данные датчиков
    Sensors mSensors;
    Course mCourse;
    //Координаты
    Coords mCoords;
    //Время
    TimeStruct mTimeStruct;
    QDateTime datetime() const;
    bool operator == (DataRecord rh);
    QString lat();
    QString lon();

    bool isCourse() const;
    //Есть ли слово курса
    bool flCourseWordEnable;
    int D1();
    int D2();
    int D3();
    int AL();
    int IG();
    int EC();
    int temperature();
    int course();
    int speed();
};

#endif // DATARECORD_H
