#include "includes.h"

#include "pictureprocessor.h"
#include "sensormanager.h"


int main() {	
	SensorManager s("config.txt");
	s.updateSensorData();
	return 0;
}