#ifndef COORDPARSER_H
#define COORDPARSER_H

#include <QObject>
#include <QDebug>
#include "message.h"
#include "course.h"
#include "extendsensor.h"
class CoordParser : public QObject
{
    Q_OBJECT
public:
    explicit CoordParser(QObject *parent = 0);
    ~CoordParser();

    Message parse( QByteArray coords, int coord_size);


    QString getFormatTime(TimeStruct time);

private:
	QString mRecords;
	// Обычная точка
	const int POINT_ORDINARY = 16;
	// Точка с курсом 
	const int POINT_COURSE   = 20;
	//Точка с датчиками
	const int POINT_SENSORS  = 32;
};

#endif // COORDPARSER_H
