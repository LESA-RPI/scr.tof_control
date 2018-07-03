// STL includes
#include "includes.h"
// #include "socket.cpp/src/tcp/tcp_server.hpp"

class SensorManager {
	private:
		DriverManager& dm = DriverManager::getInstance();
		std::vector<std::string> sensorURLs;
		std::vector<bool> door_state;
		int num_sensors;
		Sensor** sensors;
		Dist500** dists;
		PictureProcessor** procs;
		std::vector<std::string>* data;

	public:
		SensorManager(const std::string& configFile, std::vector<std::string>* data_) {
			dm.createAndActivateDefaultDrivers();
			readConfig(configFile);
			sensors = new Sensor*[num_sensors];
			dists = new Dist500*[num_sensors];
			procs = new PictureProcessor*[num_sensors];
			data_->resize(sensorURLs.size(),"");
			data = data_;
		}

		~SensorManager() {
 		    dm.shutdownAllDrivers();
			delete[] procs;
			delete[] dists;
		}

		void startUpdating() {
			
			for (unsigned int i = 0; i < sensorURLs.size(); ++i) {

				if(door_state[i] == true){
					continue;
				}

				sensors[i] = &dm.getSensorFor(sensorURLs[i]);
				dists[i] = new Dist500(*sensors[i]);
				procs[i] = new PictureProcessor(i, data);
				procs[i]->PictureSink::attachSource(dists[i]);
				dists[i]->setDoorState(2, 6, 100, 100);
				door_state[i] = true;
				dists[i]->startCounting();
				dists[i]->startPictureAcquisision();
				dists[i]->enableInstallationMode(InstallationModeController::Full16, 0, 0, 0, 0, 0);

			}

		}

		void stopUpdating() {
			for (unsigned int i = 0; i < sensorURLs.size(); ++i) {

				//if door has not been initalized it can not be closed
				if(door_state[i] == false){
					continue;
				}

				dists[i]->setDoorState(2, 6, 0, 0);
				door_state[i] = false;
				dists[i]->stopCounting();
				dists[i]->stopPictureAcquisision();
				dists[i]->disableInstallationMode();
			}
		}

		std::string getMessage(std::string msg) {

			if(msg == "start_counting") {
				this->startUpdating();
				return "started counting";
			}

			else if(msg == "stop_counting"){
				this->stopUpdating();
				return "stopped counting";
			}

			else if(msg.substr(0,8) == "get_data"){
				std::string sens_num = msg.substr(8);

				if(sens_num == ""){
					return "no sensor id given";
				}

				try{
					int sens_id = std::stoi(sens_num);
					if(sens_id >= 0 && sens_id < this->sensorURLs.size()){
						return this->data->at(sens_id);
					}

					return "what u doin m80";
				}
				catch(std::exception &e){
					return "not a valid sensor id";
				}

			}
			return msg.substr(0,8);

		}

	private:
		void readConfig(const std::string& s) {
			std::fstream config;
			config.open(s.c_str());
			std::string buffer;
			while (config >> buffer) {
				//std::cout << buffer << std::endl;
				this->sensorURLs.push_back(buffer);
				this->door_state.push_back(false);
			}
			config.close();
			num_sensors = sensorURLs.size();
		}
};

// SensorManager& SensorManager::operator=(const SensorManager& s) {
// 			return s;
// }