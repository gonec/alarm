#include "coordparser.h"
#include <QDebug>
#include <QDataStream>

CoordParser::CoordParser(QObject *parent) : QObject(parent)
{

}

CoordParser::~CoordParser()
{

}

Message CoordParser::parse(QByteArray records, int point_size)
{
    //qDebug()<<" POINT SIZE"<<point_size;
    if ( point_size == 0 ) {
        Message msg;
        msg.flValid = false;
        return msg;
    }
    //qDebug()<<"POINT SIZE: "<<point_size; 
    if ( (point_size == POINT_ORDINARY) || (point_size == POINT_COURSE) || (point_size == POINT_SENSORS) ) {
	//qDebug()<<"CORRECT POINT SIZE";
    }
    else
    {
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
	//qDebug()<<"POINT " <<i+1<<" POINT SIZE "<<point_size;;
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
	if (point_size == POINT_COURSE){
	    qDebug()<<"Coordparser> POINT COURSE";
	    //std::cout<<"                                "<<std::endl;	
	    //std::cout<<"POINT WITH COURSE"<<std::endl;	
	    //std::cout<<"                                "<<std::endl;	
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
           	 qDebug()<<"extend flag: "<<record.flExtend; 
	    }
            else {
                DataRecord record(timeData, coords, sensors);
           	 qDebug()<<"extend flag: "<<record.flExtend; 
                msg.addDataRecord(record);
            }

            msg.flValid = true;
        }
        else if ( point_size == POINT_SENSORS ) {
	    	qDebug()<<"Coordparser  POINT EXTEND ";
		uint crs =0;
		stream >>crs;
		Course course;
		course = *(Course*)(&crs);
            	//qDebug()<<"DATETIME "<<timeData ;
            	            
            //if (sensors.EC) {
                 //qDebug()<<"ADDING WITH COURSE";
            //}
            //else {
		const int EXTEND_SIZE = 12;
		char extend[EXTEND_SIZE];
		stream.readRawData(extend, EXTEND_SIZE);	
		QByteArray ba_extend(extend, EXTEND_SIZE);
		ExtendSensor extend_sensor(ba_extend);
		//stream>>extend_sensors;

		
		DataRecord record(timeData, coords, sensors, course, extend_sensor);
        	QString coordDateTime = record.datetime().toString("yyyy-MM-dd hh:mm:ss");
		
		qDebug()<<"MSENSORS HAS COURSE "<<sensors.EC;
            	qDebug()<<"TEMPERATURE  "<<course.mTemperatureSign<<" "<<course.mTemperature;
            	qDebug()<<"COURSE       "<<course.mCourse;
            	qDebug()<<"SPEED        "<<course.mSpeed;
		qDebug()<<"EXTEND SENSORS: " <<ba_extend.toHex();	
		qDebug()<<"DATETIME: "<<coordDateTime; 
             	msg.addDataRecord(record);
		
                //msg.addDataRecord(record);
            //}
            msg.flValid = true;

	}
	else	
	{
	    qDebug()<<"Coordparser ORDINARY POINT ";
            DataRecord record(timeData, coords, sensors);
            //qDebug()<<"ORDINARY"; 
	    //QString coordDateTime = record.datetime().toString("yyyy-MM-dd hh:mm:ss");
	    //qDebug()<<"DATETIME: "<<coordDateTime; 
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
