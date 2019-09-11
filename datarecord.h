#ifndef DATARECORD_H
#define DATARECORD_H
#include <QDate>
#include "coords.h"
#include "latlong.h"
#include "sensors.h"
#include "timestruct.h"
#include "course.h"
#include "extendsensor.h"
struct DataRecord
{
public:
    DataRecord();
     
    DataRecord( 
		TimeStruct, 
		Coords, 
		Sensors
		 ) ;
    
	DataRecord(
		 TimeStruct,
		 Coords,
		 Sensors,
		 Course
		 );

    DataRecord(
		 TimeStruct,
		 Coords,
		 Sensors,
		 Course,
		 ExtendSensor
		);
    //Данные датчиков
    Sensors mSensors;
    Course mCourse;
    //Координаты
    Coords mCoords;
    ExtendSensor mExtendSensor;
    //Время
    TimeStruct mTimeStruct;
    QDateTime datetime() const;
    bool operator == (DataRecord rh);
    QString lat();
    QString lon();

    bool isCourse() const;
    bool isExtend() const; 
    //Есть ли слово курса
    bool flCourseWordEnable;
    bool flExtend;
    int D1();
    int D2();
    int D3();
    int AL();
    int IG();
    int EC();
    int temperature();
    int A() const;
    int B() const;
    int course();
    int speed();
    QByteArray extend() const ; 
};

#endif // DATARECORD_H
