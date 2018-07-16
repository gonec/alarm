#include "coordparser.h"
#include <QDebug>
#include <QDataStream>

CoordParser::CoordParser(QObject *parent) : QObject(parent)
{

}

CoordParser::~CoordParser()
{

}

Message CoordParser::parse( QByteArray records, int point_size)
{
    //qDebug()<<" POINT SIZE"<<point_size;
    if ( point_size == 0 ){
        Message msg;
        msg.flValid = false;
        return msg;
    }
    int counter = ( records.size() / point_size ) ;
    if (counter < 1) {
        Message msg;
        msg.flValid = false;
        return msg;
    }
    Message msg;
    msg.setPointSize(point_size);
    for( int i = 0; i < counter; ++i) {
//          qDebug()<<"RECORDS SIZE  BEFOR CUTTING "<<records.size();
        uint time  = 0;
        uint lat   = 0;
        uint lon   = 0;
        uint sens  = 0;

        QDataStream stream(records);
        stream >> time;
        stream >> lat;
        stream >> lon;
        stream >> sens;

//           qDebug()<<"RECORDS SIZE  AFTER CUTTING "<<records.size();
        // Время
        TimeStruct timeData;
        timeData = *(TimeStruct*)(&time);

        // Широта
        LatLong latData;
        latData = *(LatLong*)(&lat);

        // Долгота
        LatLong lonData;
        lonData = *(LatLong*)(&lon);

        // Датчики
        Sensors sensors;
        sensors = *(Sensors*)(&sens);

        // Координаты
        Coords coords(latData, lonData);

        //Структура записей: время, координаты, датчики, в одном сообщение их может
        //быть несколько

        if (point_size==20){
            uint crs =0;
            stream >>crs;
            Course course;
            course = *(Course*)(&crs);
            /*
            qDebug()<<"MSENSORS HAS COURSE "<<sensors.EC;
            qDebug()<<"TEMPERATURE  "<<course.mTemperatureSign<<" "<<course.mTemperature;
            qDebug()<<"COURSE       "<<course.mCourse;
            qDebug()<<"SPEED        "<<course.mSpeed;
            */
            if (sensors.EC) {
                 //qDebug()<<"ADDING WITH COURSE";
                 DataRecord record(timeData, coords, sensors, course);
                 msg.addDataRecord(record);
            }
            else {
                DataRecord record(timeData, coords, sensors);
                 msg.addDataRecord(record);
            }

            msg.flValid = true;
        }
        else {
            DataRecord record(timeData, coords, sensors);
            msg.addDataRecord(record);
            msg.flValid = true;
        }
        records.remove(0, point_size);

    }

    msg.calculateDefCon();

    return msg;

}

QString CoordParser::getFormatTime(TimeStruct time)
{
    return QString("%1:%2:%3 %4.%5.%6").arg(QString::number(time.hours).rightJustified(2,'0'), QString::number(time.minuts).rightJustified(2, '0'), QString::number(time.seconds).rightJustified(2, '0'), QString::number(time.day).rightJustified(2, '0'), QString::number(time.month).rightJustified(2, '0'), QString::number(time.year));
}
