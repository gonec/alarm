#include "datarecord.h"
DataRecord::DataRecord(){

}

DataRecord::DataRecord(
			TimeStruct tm,
			Coords coords,
			Sensors sensors 
			): mCoords(coords) {
    mTimeStruct = tm;
    mSensors = sensors;
    flExtend = false;
    flCourseWordEnable = false;
}
  
DataRecord::DataRecord( 
			TimeStruct tm,
                        Coords coords,
                        Sensors sensors,
                        Course course
                       ) : 
	mCoords(coords) 
	{
	mCourse = course;
	mTimeStruct = tm;
	mSensors = sensors;
    	flExtend = false;
	flCourseWordEnable = true;
	
}
DataRecord::DataRecord(
		       TimeStruct tm,
                       Coords coords,
                       Sensors sensors,
                       Course course,
		       ExtendSensor ext_sensor
                       ): mCoords(coords) {
    mCourse = course;
    mTimeStruct = tm;
    mSensors = sensors;
    flCourseWordEnable = true;
    flExtend = true;
    mExtendSensor = ext_sensor;
}

bool DataRecord::operator == (DataRecord rh) {
    //return true;
    return (rh.mTimeStruct == this->mTimeStruct);
}
/*
if(i>1){
    qDebug() << "Seconds:"  << timeData.seconds;
    qDebug() << "Minuts:"   << timeData.minuts;
    qDebug() << "Hours:"    << timeData.hours;
    qDebug() << "Days:"     << timeData.day;
    qDebug() << "Month:"    << timeData.month;
    qDebug() << "Years:"    << timeData.year;

    qDebug() << "Доли Минуты:"      << latData.dm;
    qDebug() << "Минуты:"           << latData.minuts;
    qDebug() << "Градусы:"          << latData.deg;
    qDebug() << "Полушарие:"        << latData.hemisphere;
    qDebug() << "Признак Широты:"   << latData.pr;
    qDebug() << "Константа:"        << latData.c;

    qDebug() << "Доли Минуты:"      << lonData.dm;
    qDebug() << "Минуты:"           << lonData.minuts;
    qDebug() << "Градусы:"          << lonData.deg;
    qDebug() << "Полушарие:"        << lonData.hemisphere;
    qDebug() << "Признак Широты:"   << lonData.pr;
    qDebug() << "Константа:"        << lonData.c;
}
*/
 QDateTime DataRecord::datetime() const{
     return mTimeStruct.datetime();
 }
 QString DataRecord::lat(){
     return mCoords.mLat.showMachine();
 }
 QString DataRecord::lon(){
     return mCoords.mLon.showMachine();
 }

 int DataRecord::D1(){
    return mSensors.D1;
 }
 int DataRecord::D2(){
     return mSensors.D2;
 }

 int DataRecord::D3(){
    return mSensors.D3;
 }
 int DataRecord::AL(){
     return mSensors.AL;
 }
 int DataRecord::IG(){
     return mSensors.IG;
 }

int DataRecord::EC() {
      return ( mSensors.EC ) ? 1 : 9;
}
bool DataRecord::isCourse() const {
    return flCourseWordEnable;
}
bool DataRecord::isExtend() const {
    return flExtend;
}
int DataRecord::temperature() {
    if ( mCourse.mTemperatureSign ) {
        return  -1*mCourse.mTemperature;
    }
    else{
        return mCourse.mTemperature;
    }
}
int DataRecord::speed() {
    //qDebug()<<"S P E E D !!!!"<<mCourse.mSpeed;
    return mCourse.mSpeed;
}
int DataRecord::course(){
    return mCourse.mCourse;
}
QByteArray DataRecord::extend() const {
    return mExtendSensor.data();
}
int DataRecord::A() const {
    return mSensors.a;
}
int DataRecord::B() const {
    return mSensors.b;
}
