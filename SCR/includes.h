#define SENSORAPI_DLL
#define BOOST_ALL_NO_LIB

//STL includes
#include <iostream>
#include <fstream>
#include <vector>

// iris includes
#include "iris/dist500/Dist500.h"
#include "iris/drivers/DriverManager.h"
#include "iris/uff/UffRecorder.h"

#include <omp.h>

// namespace shortcuts
using namespace iris::dist500;
using namespace iris::drivers;
using namespace iris::uff;
using namespace iris::configuration;
