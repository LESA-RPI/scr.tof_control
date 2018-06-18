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

#ifndef IRIS_UFF_UFFDECODER_H
#define IRIS_UFF_UFFDECODER_H

// STL includes
#include <string>
#include <list>
#include <map>

// iris includes
#include "iris/Common.h"
#include "iris/dist500/PictureSource.h"
#include "iris/dist500/RegisterValuesSource.h"
#include "iris/dist500/DoorStateSource.h"
#include "iris/dist500/CountResultSource.h"
#include "iris/dist500/DebugDataSource.h"
#include "iris/configuration/Configuration.h"
#include "iris/dist500/Dist500Base.h"
#include "iris/dist500/DebugDataSource.h"
#include "iris/dist500/InstallationModeController.h"

namespace iris {

namespace legacy {
// internal class forwards
class Dist500MovieDecoder;
}

namespace uff {

class SENSORAPI UffDecoder: public iris::dist500::PictureSource, public iris::dist500::RegisterValuesSource,
        public iris::dist500::DoorStateSource, public iris::dist500::CountResultSource,
        public iris::dist500::DebugDataSource
{

protected:

    /**
     * Internal legacy decoder sclass
     */
    iris::legacy::Dist500MovieDecoder* decoder;

    /**
     * Holds the picture count (0 if file is closed)
     */
    unsigned long pictureCount;

    /**
     * Holds the current picture index (0 if file is closed)
     */
    unsigned long pictureIndex;

    /**
     * Buffers the current picture
     */
    iris::dist500::Pic picA;
    iris::dist500::Pic picB;

    /**
     * Holds the last read picture number
     */
    unsigned long pictureNumber;

    /**
     * Holds the last read timestamp
     */
    unsigned long long timestamp;

    /**
     * Holds the file open state
     */
    bool openFlag;

    /**
     * Holds the last exposure and temperature register numbers
     */
    unsigned short regNos[2];

    /**
     * Holds the last read exposure and temperature register values
     */
    unsigned short regVals[2];

    /**
     * Holds the door address
     */
    unsigned short door;

    /**
     * Holds the function area address
     */
    unsigned short fa;

    /**
     * Holds the last read left door state
     */
    unsigned char leftState;

    /**
     * Holds the last read right door state
     */
    unsigned char rightState;

    /**
     * Buffers the left door states for all pictures
     */
    unsigned char *leftStates;

    /**
     * Buffers the right door states for all pictures
     */
    unsigned char *rightStates;

    /**
     * Holds the count of single APC result events
     */
    unsigned long apcSingleResultsCount;

    unsigned long apcTotalResultsCount;

    unsigned long manualTotalResultsCount;

    unsigned long configParamCount;

    unsigned long configParamDefinitionCount;

    unsigned long configParamGroupDefinitionCount;

    iris::dist500::Picture *pictureA;
    iris::dist500::Picture *pictureB;

    iris::dist500::DoorState *doorState;

    iris::dist500::RegisterValues *values;

    iris::dist500::CountResult *countResult;

    iris::dist500::CountResult *totalApcResult;

    unsigned long doorStateCount;

    unsigned int sensorCount;

    typedef std::map<unsigned long, iris::dist500::DoorState> DoorEventMap;

    typedef std::map<unsigned long, iris::dist500::CountResult> CountEventMap;

    DoorEventMap doorEventMap;

    CountEventMap countEventMap;

    unsigned long lastDoorEventPos;

    unsigned long lastCountEventPos;

    unsigned long lastApcTotalPos;

    typedef std::list<iris::dist500::CountResult> CountResultList;

    CountResultList totalApcCounts;

    CountResultList totalManualCounts;

public:

    /**
     * Default no-arg constructor
     */
    UffDecoder();

    /**
     * Destructor
     */
    ~UffDecoder();

    /**
     * Opens a UFF file for decoding
     *
     * @param filename Name of file to be opened
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool open(const std::string& filename);

    /**
     * Closes the UFF file
     */
    void close(void);

    /**
     * Returns the current file open state
     *
     * @return <code>true</code> if file is open, <code>false</code> otherwise
     */
    bool isOpen(void);

    /**
     * Returns the number of pictures within the UFF file
     *
     * @return Number of pictures (0 if file is not open)
     */
    unsigned int getPictureCount(void);

    /**
     * Returns the current picture index
     *
     * @return 0-based picture index (0 if file is not open)
     */
    unsigned int getPictureIndex(void);

    /**
     * Sets the picture index to a new value and pushes the data to all attached sinks
     * if a) the index has effectively changed or b) if forceRefresh is set to
     * <code>true</code>
     *
     * @param index New picture index (0-based; must be < picture count)
     * @param forceRefresh Setting this flag to <code>true</code> triggers re-pushing
     *        the picture data to all sinks even if the index does not effectively
     *        change during the operation (ie if the current index already has the
     *        desired value)
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool setPictureIndex(const unsigned int index, const bool forceRefresh = false);

    /**
     * Reads the given picture and related data into buffer variables
     *
     * @param index Picture index (0-based; must be < picture count)
     * @param picNum Receives the picture number
     * @param picTime Receives the picture timestamp
     * @param picBuf Receives the pixel data
     * @param expo Receives the exposure register (!) value
     * @param temp Receives the temperature value
     * @param left Receives the left door state
     * @param right Receives the right door state
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool readPictureAndData(const unsigned char sensorIndex, const unsigned long index, unsigned long& picNum, unsigned long long& picTime, iris::dist500::Pic& picBuf,
                            unsigned short& expo, signed short& temp, unsigned char& left, unsigned char& right);

    /**
     * (Re-)pushes the current data to all attached sinks
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool repushData(const int sensorNo);

    /**
     * Returns the number of APC count result events within the UFF file
     *
     * @return Number of APC count result events (0 if file is not open)
     */
    unsigned long getSingleApcEventCount(void);

    /**
     * Returns the given APC count result event data
     *
     * @param index Event index (0-based; must be < results count)
     * @param result Receives the count result data
     *
     * @return <code>true</code> if successful, <code>false</code> otherwise
     */
    bool getSingleApcEvent(const unsigned long index, iris::dist500::CountResult& result);

    unsigned long getDoorStateCount(void);

    bool getDoorState(const unsigned int index, iris::dist500::DoorState& doorState);

    unsigned char getSensorCount(void);

    unsigned long getTotalApcResultCount(void);

    bool getTotalApcResult(const unsigned long index, int& intervalIndex, int& countIndex, iris::dist500::CountResult& result);

    unsigned long getTotalManualResultCount(void);

    bool getTotalManualResult(const unsigned long index, int& intervalIndex, int& countIndex, iris::dist500::CountResult& result, std::string& comment);

    unsigned long getConfigurationParameterCount(const unsigned char sensorNo);

    bool getConfigurationParameter(const unsigned char sensorNo, const unsigned long index, unsigned short& groupId, unsigned short& paramId, unsigned short& size, void* buffer);

    unsigned long getConfigurationParameterDefinitionCount(const unsigned char sensorNo);

    bool getConfigurationParameterDefinition(const unsigned char sensorNo, const unsigned long index, unsigned short& groupId, unsigned short& paramId, char* nameBuffer, const unsigned short maxNameLen, int& dataType, unsigned short& arraySize, int& updateType, signed long& minVal, signed long& maxVal, signed long& defVal, unsigned short& size, void* buffer);

    unsigned long getConfigurationParameterGroupDefinitionCount(const unsigned char sensorNo);

    bool getConfigurationParameterGroupDefinition(const unsigned char sensorNo, const unsigned long index, unsigned short& groupId, char* nameBuffer, const unsigned short maxNameLen);

    bool readSensorConfiguration(const unsigned char sensorNo, iris::configuration::Dist500Configuration& config);

    bool readSensorConfiguration(const unsigned char sensorNo, iris::configuration::Dist500Configuration& config, iris::dist500::Dist500Base::ConfigurationMismatches& mismatches);

    bool hasSensorConfiguration(const unsigned char sensorNo);

    bool hasSensorConfiguration(void);

    bool getPictureAndTimeBases(const unsigned char sensorNo, unsigned long& pictureBase, unsigned long long& timeBase);

    static void enableUtf8(void);

    static void disableUtf8(void);

    static bool utf8Active(void);

    //bool getMetadata(int groupNumber, char *serial, char *firmware);

    bool readDataSourceInfos(const unsigned char sensorAddr, iris::dist500::InstallationModeController::DataSourceInfoList& infos);

    int getDebugDataCount(void);

    iris::dist500::DebugData* readDebugData(int index);

protected:

    typedef std::map<unsigned char, iris::dist500::Dist500Base::TemporaryConfiguration*> ConfigurationMap;

    mutable ConfigurationMap cachedConfigurations;

    void clearConfigurationCache(void);

}; // class UffDecoder

} // namespace uff

} // namespace iris

#endif // IRIS_UFF_UFFDECODER_H
