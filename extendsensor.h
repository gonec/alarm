#ifndef EXTEND_SENSOR
#define EXTEND_SENSOR
#include <QByteArray>
class ExtendSensor {
	public:
		ExtendSensor();
		ExtendSensor(QByteArray arr);
		QByteArray data() const;
	private:
		QByteArray mExtend;			
};
#endif
