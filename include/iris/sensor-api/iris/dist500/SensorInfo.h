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

#ifndef DIST500_SENSORINFO_H
#define DIST500_SENSORINFO_H

// STL includes
#include <string>

// iris includes
#include "iris/Common.h"

namespace iris {

namespace dist500 {

// forward declarations to prevent #include cycles
class SensorGroup;
class FirmwareController;

/**
 * Cache object for sensor meta information
 */
class SENSORAPI SensorInfo {

protected:

    /**
     * Serial number (device number) in format xx_yyyyy (x and y decimal digits)
     */
    std::string serial;

    /**
     * Sensor type name
     */
    std::string typeName;

    /**
     * API connection URL
     */
    std::string url;

    /**
     * API driver name
     */
    std::string driverName;

    /**
     * API driver version
     */
    std::string driverVersion;

    /**
     * Name of firmware
     */
    std::string firmwareName;

    /**
     * Version of firmware
     */
    std::string firmwareVersion;

    /**
     * Version of FPGA firmware, ex. CD
     */
    std::string fpgaFirmwareVersion;

    /**
     * Timestamp of firmware
     */
    std::string firmwareTimestamp;

    /**
     * Sensor location
     */
    std::string location;

    /**
     * Sensor usage
     */
    std::string usage;

    /**
     * Name of sensor icon
     */
    std::string iconName;

    /**
     * May hold the corresponding FirmwareController instance
     * (0 if not associated)
     */
    FirmwareController* sensor;

    /**
     * Function area number
     */
    unsigned short functionArea;

    /**
     * Door number
     */
    unsigned short doorNumber;

    /**
     * Index within a group
     */
    unsigned short groupIndex;

    bool errors;

public:

    /**
     * Constructor
     *
     * @param serial Serial number
     * @param typeName Type name
     * @param url URL
     * @param driverName Driver name
     * @param driverVersion Driver version
     * @param firmwareName Firmware name
     * @param firmwareVersion Firmware version
     * @param fpgaFirmwareVersion FPGA firmware version
     * @param firmwareTimestamp Firmware timestamp
     * @param location Sensor location
     * @param usage Current usage
     * @param iconName Icon name
     * @param functionArea Function area number
     * @param doorNumber Door number
     * @param groupIndex Index within a sensor group
     * @param sensor FirmwareController instance (or 0)
     */
    SensorInfo(const std::string& serial, const std::string& typeName,
            const std::string& url, const std::string& driverName,
            const std::string& driverVersion, const std::string& firmwareName,
            const std::string& firmwareVersion, const std::string& fpgaFirmwareVersion,
            const std::string& firmwareTimestamp, const std::string& location,
            const std::string& usage, const std::string& iconName,
            unsigned short functionArea, unsigned short doorNumber,
            unsigned short groupIndex, FirmwareController* sensor);

    /**
     * No-arg constructor
     */
    SensorInfo();

    /**
     * Returns the driver name
     *
     * @return Driver name
     */
    std::string getDriverName(void) const;

    /**
     * Returns the driver version
     *
     * @return Driver version
     */
    std::string getDriverVersion(void) const;

    /**
     * Returns the firmware name
     *
     * @return Firmware name
     */
    std::string getFirmwareName(void) const;

    /**
     * Returns the firmware timestamp
     *
     * @return Firmware timestamp
     */
    std::string getFirmwareTimestamp(void) const;

    /**
     * Returns the firmware version
     *
     * @return Firmware version
     */
    std::string getFirmwareVersion(void) const;
    
    /**
     * Returns the FPGA firmware version
     *
     * @return FPGA firmware version
     */
    std::string getFpgaFirmwareVersion(void) const;

    /**
     * Returns the icon name
     *
     * @return Icon name
     */
    std::string getIconName(void) const;

    /**
     * Returns the sensor location
     *
     * @return Sensor location
     */
    std::string getLocation(void) const;

    /**
     * Returns the serial number
     *
     * @return Serial number
     */
    std::string getSerial(void) const;

    /**
     * Returns the type name
     *
     * @return Type name
     */
    std::string getTypeName(void) const;

    /**
     * Returns the URL
     *
     * @return URL
     */
    std::string getUrl(void) const;

    /**
     * Returns the current usage
     *
     * @return Current usage
     */
    std::string getUsage(void) const;

    /**
     * Returns the function area number
     *
     * @return Function area number
     * @see CounterController::getFunctionAreaStatuses
     */
    unsigned short getFunctionArea(void) const;

    /**
     * Returns the door number
     *
     * @return Door number
     */
    unsigned short getDoorNumber(void) const;

    /**
     * Returns the index within a sensor group
     *
     * @return Group index
     */
    unsigned short getGroupIndex(void) const;

    /**
     * Returns the associated sensor, if any
     *
     * @return FirmwareController instance if present,
     *         0 otherwise
     */
    FirmwareController* getSensor(void) const;

    bool containsErrors(void) const;

    void signalErrors(void);

}; // class SensorInfo

// TODO encapsulate firmware info in a separate class

} // namespace dist500

} // namespace iris

#endif // DIST500_SENSORINFO_H
