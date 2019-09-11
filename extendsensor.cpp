#include "extendsensor.h"

ExtendSensor::ExtendSensor() {

}

ExtendSensor::ExtendSensor(QByteArray bt) {
	mExtend = bt;
}

QByteArray ExtendSensor::data() const {
	return mExtend;
}
