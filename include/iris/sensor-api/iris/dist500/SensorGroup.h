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

#ifndef DIST500_SENSORGROUP_H
#define DIST500_SENSORGROUP_H

// STL includes
#include <list>
#include <string>

// iris includes
#include "iris/Common.h"
#include "Dist500.h"

namespace iris {

namespace dist500 {

/**
 * Represents a group of DIST500 sensors (eg a function area). Sensors are usually grouped for wide doors.
 */
class SENSORAPI SensorGroup {

public:

    typedef std::list<Dist500*> SensorList;

protected:

    unsigned short groupNumber;

    SensorList slaves;

    std::string description;

    std::string location;

    std::string subLocation;

    unsigned short functionArea;

    unsigned short doorNumber;

    Dist500* master;

public:

    SensorGroup(const unsigned short groupNumber, const std::string& description, const std::string& location, const std::string& subLocation, const unsigned short functionArea, const unsigned short doorNumber);

    /**
     * adds a sensor. The first sensor is added as the "master" sensor, others are added as slaves. The master sensor is responsible for sending total count results.
     * @param sensor
     */
    void addSensor(Dist500* sensor);

    /**
     * Removes all sensors from the SensorGroup and deletes the pointers.
     * @note Be careful with this call as the deleting may invalidate instances in other places of your program.
     */
    void removeAndDeleteAll(void);

    /**
     * Returns total number of sensors, both master and slave.
     * @return 
     * @see getSlaveCount
     */
    int getSensorCount(void) const;

    /**
     * Returns number of slave sensors in the group.
     * @see addSensor
     * @see getSensorCount
     * @see getSlaveSensor
     */
    int getSlaveCount(void) const;

    std::string getDescription(void) const;

    std::string getLocation(void) const;

    std::string getSubLocation(void) const;

    Dist500* getMasterSensor(void);

    Dist500* getSlaveSensor(const unsigned int index);

    unsigned short getGroupNumber(void) const;

    unsigned short getFunctionArea(void) const;

    unsigned short getDoorNumber(void) const;

    bool operator< (const SensorGroup& comp);

    void setGroupNumber(unsigned short gn);

}; // class SensorGroup

} // namespace dist500

} // namespace iris

#endif // DIST500_SENSORGROUP_H
