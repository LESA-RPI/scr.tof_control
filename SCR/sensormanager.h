// STL includes
#include "includes.h"

class SensorManager {
	private:
		DriverManager& dm = DriverManager::getInstance();
		std::vector<std::string> sensorURLs;
		int num_sensors;
		Sensor** sensors;
		Dist500** dists;
		PictureProcessor** procs;

	public:
		SensorManager(const std::string& configFile) {
			dm.createAndActivateDefaultDrivers();
			readConfig(configFile);
			sensors = new Sensor*[num_sensors];
			dists = new Dist500*[num_sensors];
			procs = new PictureProcessor*[num_sensors];
		}

		~SensorManager() {
 		    dm.shutdownAllDrivers();
			delete[] procs;
			delete[] dists;
		}

		void startUpdating() {
			
			for (unsigned int i = 0; i < sensorURLs.size(); ++i) {

				sensors[i] = &dm.getSensorFor(sensorURLs[i]);
				dists[i] = new Dist500(*sensors[i]);
				procs[i] = new PictureProcessor(i);
				procs[i]->PictureSink::attachSource(dists[i]);
				dists[i]->setDoorState(2, 6, 100, 100);
				dists[i]->startCounting();
				dists[i]->startPictureAcquisision();
				dists[i]->enableInstallationMode(InstallationModeController::Full16, 0, 0, 0, 0, 0);

			}

		}

		void stopUpdating() {
			for (unsigned int i = 0; i < sensorURLs.size(); ++i) {
				dists[i]->setDoorState(2, 6, 0, 0);
				dists[i]->stopCounting();
				dists[i]->stopPictureAcquisision();
				dists[i]->disableInstallationMode();
			}
		}

	private:
		void readConfig(const std::string& s) {
			std::fstream config;
			config.open(s.c_str());
			std::string buffer;
			while (config >> buffer)
				this->sensorURLs.push_back(buffer);
			config.close();
			num_sensors = sensorURLs.size();
		}
};
