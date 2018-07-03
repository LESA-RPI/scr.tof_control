#include "includes.h"

#include "pictureprocessor.h"
#include "sensormanager.h"

#define PORT 3660
#include "TCPServer.h"
#include <iostream>


TCPServer tcp;

void * loop(void * m)
{
    pthread_detach(pthread_self());
    std::vector<std::string>* sensor_data = new std::vector<std::string>;
	SensorManager s("config.txt", sensor_data);
	while(true){
		srand(time(NULL));
		std::string command = tcp.getMessage();
		if(command != ""){
			std::string data = s.getMessage(command);
			if(data == ""){
				data = "no data yet";
			}
			tcp.Send(data);
			tcp.clean();
		}
		//usleep(1000);
	}
	tcp.detach();
	delete [] sensor_data;
}

int main()
{
	
	
	pthread_t msg;
	tcp.setup(PORT);
	if( pthread_create(&msg, NULL, loop, (void *)0) == 0)
	{
		tcp.receive();
	}
	return 0;
}