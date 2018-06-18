#define SENSORAPI_DLL
#define BOOST_ALL_NO_LIB

// STL includes
#include <iostream>


// iris includes
#include "iris/dist500/Dist500.h"
#include "iris/drivers/DriverManager.h"
#include "iris/uff/UffRecorder.h"

// namespace shortcuts
using namespace iris::dist500;
using namespace iris::drivers;
using namespace iris::uff;
using namespace iris::uip;
using namespace iris::configuration;
using namespace std;


#define SENSOR_URL "udp://10.3.3.83#1"
#define SENSOR_URL_0 "udp://10.3.3.83#1"
#define SENSOR_URL_1 "udp://10.3.3.73#1"
#define SENSOR_URL_2 "udp://10.3.3.63#1"
#define SENSOR_URL_3 "udp://10.3.3.53#1"
#define SENSOR_URL_4 "udp://10.3.3.43#1"
#define SENSOR_URL_5 "udp://10.3.3.33#1"
#define SENSOR_URL_7 "udp://10.3.3.13#1"
#define SENSOR_URL_8 "udp://10.3.3.12#1"
#define SENSOR_URL_9 "udp://10.3.3.11#1"
#define SENSOR_URL_10 "udp://10.3.3.23#1"
#define SENSOR_URL_11 "udp://10.3.3.31#1"
#define SENSOR_URL_12 "udp://10.3.3.41#1"
#define SENSOR_URL_13 "udp://10.3.3.53#1"
#define SENSOR_URL_14 "udp://10.3.3.61#1"
#define SENSOR_URL_15 "udp://10.3.3.71#1"
#define SENSOR_URL_16 "udp://10.3.3.81#1"
#define SENSOR_URL_17 "udp://10.3.3.82#1"

double sumg=0;

#ifndef SENSOR_URL
#error NO VALUE FOR #define SENSOR_URL, CHECK SOURCE CODE
#else




int main()
{
	DriverManager& dm = DriverManager::getInstance();
	dm.createAndActivateDefaultDrivers();

	Driver::AddressList al = dm.scanAllDevices();
	// // print list with some additional information to console
	cout << al.size() << " sensor(s) found:\n";


	
	// // create DIST500 instance
	Sensor& s = dm.getSensorFor(SENSOR_URL);
	Dist500* dist = new Dist500(s);

	
	// //count people
	dist->setWorkingMode(normal_mode);
	dist->startCounting();
	Dist500::CountList cl;

	unsigned short fa = 1;
 	unsigned short door = 1;
 	unsigned char left = 0, right = 0;
 	dist->getDoorState(fa, door, left, right);
    if (!left && ! right) {
        cout << "door is closed\n";
    }
    else {
        cout << "door is open\n";
    }

	// Sleep(10000);
	// dist->getCountResults(fa, buffer_counter, true, 0x01, cl);
	// cout << buffer_counter << endl;
	
	// dist->getCountResults(fa, buffer_counter, true, 0xff, cl);
	// cout << buffer_counter << endl;
	// for (Dist500::CountList::iterator i = cl.begin(); i != cl.end(); ++i) {
	// 	category_counts cc = *i;
	// 	cout << "cat " << (int)(cc.categoryId) << ": in " << cc.boarding << " / out " << cc.alighting << endl;
	// }
	

	cout << "yay" << endl;
	//dist->stopCounting();
	//Sleep(500000);
	
    dm.shutdownAllDrivers();
	
	return 0;

}
#endif