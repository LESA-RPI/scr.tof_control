// ***************************************************************************
// *    _      _       ____                                 _    ____ ___    *
// *   (_)_ __(_)___  / ___|  ___ _ __  ___  ___  _ __     / \  |  _ \_ _|   *
// *   | | '__| / __| \___ \ / _ \ '_ \/ __|/ _ \| '__|   / _ \ | |_) | |    *
// *   | | |  | \__ \  ___) |  __/ | | \__ \ (_) | |     / ___ \|  __/| |    *
// *   |_|_|  |_|___/ |____/ \___|_| |_|___/\___/|_|    /_/   \_\_|  |___|   *
// *                                                                         *
// *   Copyright (c) 2010 by iris-GmbH, Berlin         All rights reserved   *
// *                                                                         *
// ***************************************************************************

// ---------------------------------------------------------------------------
// Please refer to LICENSE.TXT for more information on copyright and licensing
// terms with respect to this library and its source codes.
// ---------------------------------------------------------------------------

#ifndef UFF_UFFRECORDER_H
#define UFF_UFFRECORDER_H

// STL includes
#include <string>

// iris includes
#include "iris/Common.h"
#include "iris/dist500/PictureSink.h"
#include "iris/dist500/RegisterValuesSink.h"
#include "iris/dist500/DoorStateSink.h"
#include "iris/dist500/CountResultSink.h"
#include "iris/dist500/DebugDataSink.h"
#include "iris/dist500/SensorInfoProvider.h"
#include "iris/dist500/Dist500.h"
#include "PictureRingBuffer.h"
#include "iris/synchronization/Event.h"
#include "iris/synchronization/Mutex.h"

namespace iris {

namespace legacy {
// internal class forwards
class Dist500MovieBuilder;
}

namespace uff {

/**
 * Implements a DIST500 movie recorder
 */
class SENSORAPI UffRecorder: public iris::dist500::PictureSink, public iris::dist500::RegisterValuesSink, public iris::dist500::DoorStateSink,
        public iris::dist500::CountResultSink, public iris::dist500::DebugDataSink {

protected:

    bool dummyMode;

    /**
     *
     */
    iris::legacy::Dist500MovieBuilder* builder;

    /**
     *
     */
    std::string fileName;

    /**
     *
     */
    std::string appName;

    /**
     *
     */
    std::string appVersion;

    /**
     *
     */
    int pictureCount;

    /**
     *
     */
    UffRecorder *existing;

    /**
     *
     */
    bool open;

    iris::dist500::SensorInfo sensorInfo;

    unsigned long basePictureNumber;

    unsigned long long baseTimestamp;

    //PictureRingBuffer buffer;

    iris::synchronization::Event endOfRecording;

    std::string userName;

    std::string location;

    int intervalIndex;

    int countIndex;

    void openUnderlyingBuilder(void);

    void closeUnderlyingBuilder(void);

    bool stopping;

    iris::synchronization::Mutex baseValuesMutex;

    iris::synchronization::Mutex accessMutex;

public:


    /**
     * Constructor
     *
     * @param fileName Name of UFF file to be created
     * @param appName Application name string
     * @param appVersion Application version string
     * @param userName User name string
     * @param location Location description string
     * @param provider Provider of SensorInfo
     */
    UffRecorder(const std::string& fileName, const std::string appName,
                const std::string appVersion,
                const std::string& userName, const std::string& location,
                iris::dist500::SensorInfoProvider* provider/*, iris::dist500::PictureSource* pictureSource, iris::dist500::RegisterValuesSource* registerSource, iris::dist500::DoorStateSource* doorSource, iris::dist500::CountResultSource *countSource*/);

    /**
     * Constructor
     *
     * @param existing Existing UffRecorder instance to join
     * @param provider Provider of SensorInfo
	 *
     * @note Use this constructor variant for slaves of a sensor group. UffRecorder instance
     *       of master sensor has to be given as parameter existing
     */
    UffRecorder(UffRecorder* existing, iris::dist500::SensorInfoProvider* sensorInfoProvider/*,
                iris::dist500::PictureSource* pictureSource, iris::dist500::RegisterValuesSource* registerSource, iris::dist500::DoorStateSource* doorSource, iris::dist500::CountResultSource *countSource*/);

    UffRecorder(const std::string& fileName, const std::string appName,
                const std::string appVersion,
                const std::string& userName, const std::string& location/*,
                iris::dist500::Dist500* sensor*/);

    UffRecorder(UffRecorder* existing/*, iris::dist500::Dist500* sensor*/);

    /**
     * Destructor
     */
    virtual ~UffRecorder();

    /**
     * Starts writing of data from attached sources to UFF file
     *
     * @param maxPictures Picture count limit for recording
     * @param maxTime Time limit for recording (ms)
	 *
     * @note Recording is lasting until call of method stopRecording if started
     *       with default parameters maxPictures == 0 and maxTime == 0
     */
    void startRecording(unsigned long maxPictures = 0,
            unsigned long long maxTime = 0);

    /**
     * Stops writing of data to UFF file
     */
    void stopRecording(void);

    void adjustBaseValues(iris::dist500::PictureBoundData* data);

    /**
     *
     */
    void processNewPicture(iris::dist500::Picture* picture,
            unsigned long pictureIndex, unsigned long pictureIndexCount);

    /**
     * Waits for end of recording (writing of data to UFF file). Useful only if
	 * recording was started with parameter maxPictures > 0 or maxTime > 0
     *
     * @param timeoutMs Timeout for waiting (ms)
     *
     * @return <code>true</code> if no timeout occured while waiting, <code>false</code>
     *         otherwise
     */
    bool waitForEndOfRecording(int timeoutMs);

    void processNewCountResult(iris::dist500::CountResult* result,
                unsigned long countResultIndex, unsigned long countResultCount);

    void processNewDoorState(iris::dist500::DoorState* state,
                unsigned long pictureIndex, unsigned long pictureIndexCount);

    void processNewRegisterValues(iris::dist500::RegisterValues* values,
                                  unsigned long pictureIndex, unsigned long pictureIndexCount);

    bool writeTotalApcCountResult(const int intervalIndex, const int countIndex, const unsigned short category, const unsigned short boarding, const unsigned short alighting);

    bool writeTotalManualCountResult(const int intervalIndex, const int countIndex, const unsigned short category, const unsigned short boarding, const unsigned short alighting, const std::string& comment);

    bool writeSensorConfiguration(const unsigned char sensorNo, iris::configuration::Dist500Configuration& config);

    bool writeSensorConfiguration(const unsigned char sensorNo, iris::configuration::Dist500Configuration& config, iris::dist500::Dist500Base::ConfigurationMismatches& mismatches);

    bool writeMetadataField(const int fieldId, const std::string& text);

    void processNewDebugData(iris::dist500::DebugData* data, unsigned long dataIndex, unsigned long dataCount);

    /**
     * Detaches all data sources
     */
    void detachAll(void);

    void enableDummyMode(void);

    bool writeInitialDoorState(const unsigned short doorNumber, const unsigned char leftState, const unsigned char rightState);

    /**
     * Attaches all data sources of sensor
     *
     * @param sensor Sensor with data sources to be attached
     */
    void attachAll(iris::dist500::Dist500* sensor);

    /**
     * Enables UTF-8 support. UFF file name and all strings written to UFF file
     * are expected with UTF-8 encoding
     */
    static void enableUtf8(void);

    /**
     * Disables UTF-8 support. UFF file name and all strings written to UFF file
     * are expected with ANSI encoding
     */
    static void disableUtf8(void);

    /**
     * Checks whether UTF-8 support is enabled or not
     *
     * @return <code>true</code> if UTF-8 support is enabled, <code>false</code>
     *         otherwise
     */
    static bool utf8Active(void);

    bool saveDataSourceInfos(const unsigned char sensorAddr, const iris::dist500::InstallationModeController::DataSourceInfoList& infos);

protected:

    bool _writeSensorConfiguration(const unsigned char sensorNo, iris::configuration::Configuration& config);

}; // class UffRecorder

} // namespace uff

} // namespace iris

#endif // UFF_UFFRECORDER_H
