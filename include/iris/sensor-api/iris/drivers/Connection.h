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

#ifndef DRIVERS_CONNECTION_H
#define DRIVERS_CONNECTION_H

// STL includes
#include <map>
#include <string>

// iris includes
#include "iris/Common.h"
#include "iris/drivers/Sensor.h"
#include "iris/synchronization/Mutex.h"

namespace iris {

namespace drivers {

class Driver;

/**
 * Represents a communication object capable of communicating with one sensor
 * (or several sensors) using a Driver instance
 */
class SENSORAPI Connection {

protected:

    /**
     * Associated driver instance
     */
    Driver& driver;

    /**
     * Sensor address (without prefix and :// separator)
     */
    std::string addr;

    /**
     * Constructor.
     * Creates a new Connection instance for the given driver and address
     *
     * @param driver Driver instance
     * @param addr Sensor address (without prefix and ://)
     *
     */
    Connection(Driver& driver, const std::string& addr);

    /**
     * Destructor.
     * Also frees the associated Sensor instance if it exists
     */
    virtual ~Connection();

    friend class Driver;

    /**
     * Creates a new Sensor instance for the Connection.
     * Will usually be overloaded by concrete driver implementations to provide
     * specialized Sensor subclasses.
     *
     * @param address Sensor address without driver prefix
     *
     * @return New Sensor instance
     */
    virtual Sensor* createSensor(const std::string& address);

    /**
     * Returns the associated Sensor instance
     *
     * @param addr Sensor address
     *
     * @return Sensor instance
     */
    Sensor& getSensor(const std::string& addr);

public:

    /**
     * Returns the URL prefix
     *
     * @return URL prefix (without :// separator)
     */
    std::string getUrlPrefix(void) const;

    /**
     * Returns the sensor address
     *
     * @return Sensor address (without prefix and :// separator)
     */
    std::string getAddr(void) const;

    /**
     * Returns the sensor URL
     *
     * @return Full sensor URL (including prefix, :// separator and address)
     */
    std::string getUrl(void) const;

    /**
     * Returns the corresponding driver
     *
     * @return Driver instance
     */
    Driver& getDriver(void) const;

    /**
     * Sends the given message using the transport
     *
     * @param level UIP level (0..2)
     * @param msg Message to be sent
     */
    void sendMessage(const int level, UipMessage* msg);

    /**
     * Sends the given message in broadcast mode using the transport
     *
     * @param level UIP level (0..2)
     * @param msg Message to be sent
     */
    void sendBroadcastMessage(const int level, UipMessage* msg);

    /**
     * Maps sensor addresses to Sensor instances
     */
    typedef std::map<std::string, Sensor*> SensorMap;

    /**
     * Holds the current address / Sensor instance associations
     */
    SensorMap sensorMap;

    /**
     * Registers a sensor instance
     *
     * @param address Sensor address
     */
    void registerSensor(const std::string& address, Sensor* sensorInstance = 0);

    /**
     * Unregisters a sensor instance
     *
     * @param address Sensor address
     */
    void unregisterSensor(const std::string& address);
    
    /**
     * Unregisters an address but does not delete the sensor instance (useful when updating its address, DHCP)
     *
     * @param address Sensor address
     */
    void unregisterAddressKeepSensor(const std::string& address);

    /**
     * Dispatches an incoming message to the destination sensor
     *
     * @param level UIP level (0..2)
     * @param addr Sensor address
     * @param msg Message to be delivered
     */
    void dispatchMessage(const int level, const std::string addr,
            const UipMessage* msg);

    iris::synchronization::Mutex& getExclusionGroupMutex(void);

    iris::synchronization::Mutex privateAccessMutex;

    iris::synchronization::Mutex& getAccessMutex(void);

    iris::synchronization::Mutex mutex;
    
    /**
     * @brief setAddress Safely sets a new address for this connection. This allows the address part or UIP part to change.
     * @param newAddress
     * @note Accepts addresses including or not including the hash+UIP part. Default for that is "#1".
     */
    void setAddress(const std::string& newAddress);

}; // class Connection

} // namespace drivers

} // namespace iris

#endif // DRIVERS_CONNECTION_H
