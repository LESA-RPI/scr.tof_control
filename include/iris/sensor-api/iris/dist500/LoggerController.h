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

#ifndef DIST500_LOGGERCONTROLLER_H
#define DIST500_LOGGERCONTROLLER_H

// iris includes
#include "iris/Common.h"
#include "iris/drivers/Sensor.h"
#include "iris/dist500/Dist500Base.h"

namespace iris {

namespace dist500 {

typedef struct {
    iris::uip::ulong messageID;
    iris::uip::ulong timestamp;
    iris::uip::ulong sensorStartCount;
    iris::uip::log_level_enumeration logLevel;
    iris::uip::support_level_enumeration supportLevel;
    iris::uip::log_info_code_enumeration infoCode;
    std::string messageCategory;
    std::string messageText;
} LogMessage;

typedef std::map<uint16_t, LogMessage> LogMap;

typedef struct {
    std::string updateId;
    uip::ulong updateTimestamp;
    uip::update_status_enumeration updateStatus;
    bool componentApplicationVersionChanged;
    uip::char_array_32Bytes componentApplicationVersion;
    bool componentFpga1VersionChanged;
    uip::char_array_32Bytes componentFpga1Version;
    bool componentFpga2VersionChanged;
    uip::char_array_32Bytes componentFpga2Version;
    bool componentConfigurationVersionChanged;
    uip::char_array_32Bytes componentConfigurationVersion;
    std::string updateUrl;
    std::string updateDetails;
} UpdateHistoryEntry;

typedef std::map<uint16_t, UpdateHistoryEntry> UpdateHistoryMap;

/**
 * @brief The LoggerController class provided access to the sensor's logger and operation time counter.
 */
class SENSORAPI LoggerController: virtual public Dist500Base {
public:
    LoggerController(iris::drivers::Sensor& sensor);
    ~LoggerController();
    
    SENSOR_RESULT deleteAllLogEntries(std::string& errorString);
    
    SENSOR_RESULT getLogEntries(iris::uip::ushort numberOfEntries, iris::uip::support_level_enumeration supportLevelEnumeration, LogMap& logMap, std::string& errorString);
    
    SENSOR_RESULT getOperationTimeCounter(iris::uip::operation_time_counter_enumeration counterType, iris::uip::ulonglong& operationTime, iris::uip::ulong& numberOfEvents, std::string& errorString);
    
    SENSOR_RESULT getUpdateHistoryEntries(iris::uip::ushort numberOfEntries, UpdateHistoryMap& logMap, std::string& errorString);
    
private:

    SENSOR_RESULT requestLogEntries(iris::uip::ushort numberOfEntries, iris::uip::support_level_enumeration supportLevelEnumeration, iris::uip::ushort& outTotalEntries, LogMap& outLogMap, std::string& errorString);

    SENSOR_RESULT requestUpdateHistoryEntries(iris::uip::ushort numberOfEntries, iris::uip::ushort& outTotalEntries, UpdateHistoryMap& UpdateHistoryMap, std::string& errorString);

    LoggerController(const LoggerController&);// forbid
    LoggerController& operator=(const LoggerController&);// forbid
};

} // namespace dist500

} // namespace iris

#endif // DIST500_LOGGERCONTROLLER
