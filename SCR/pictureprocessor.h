// STL includes
#include "includes.h"
const double DATA_CORRECTION=5000.0/4096.0;

// sample class to demonstrate custom picture procs[i]essing
class PictureProcessor: public PictureSink {

	private:
		int sensorId;
		std::vector< std::vector<int> > data;


		void saveData() {
			std::stringstream ss;
			ss << "output-" << sensorId << ".txt";
			std::ofstream myfile (ss.str().c_str());

			for (int y = 0; y < 25; y++) {
				for (int x = 0; x < 20; x++)
					myfile << data[y][x] << "\t";
				myfile << std::endl;
			}

			myfile.close();
		}

	public:
		PictureProcessor(int id) {
			sensorId=id;
			data.resize(25, std::vector<int> (20, 0));
			dataAcquired=false;
		}

		int getSensorId() {
			return this->sensorId;
		}

		std::vector< std::vector<int> >& getData() {
			return this->data;
		}

	protected:
		bool dataAcquired;
		void processNewPicture(Picture *picture, unsigned long pictureIndex, unsigned long pictureIndexCount) {
			if (!dataAcquired) {
				Pic* pic = picture->getPicture();

				for (int x = 0; x < 20; x++)
					for (int y = 0; y < 25; y++)
						data[y][x] = pic->subPictures.distances.matrix[x][y].decoded.value*DATA_CORRECTION;
				saveData();
			}
		}
};
