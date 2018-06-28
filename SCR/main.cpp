#include "includes.h"

#include "pictureprocessor.h"
#include "sensormanager.h"


int main() {	
	std::vector<std::string>* sensor_data;
	SensorManager s("config.txt", sensor_data);
	s.startUpdating();
	while (true);
	return 0;
}