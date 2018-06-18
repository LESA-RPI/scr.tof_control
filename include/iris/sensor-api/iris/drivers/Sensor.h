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

#ifndef DRIVERS_SENSOR_H
#define DRIVERS_SENSOR_H

// STL includes
#include <string>

// iris includes
#include "iris/Common.h"
#include "iris/drivers/MultiMailBox.h"
#include "iris/synchronization/Mutex.h"

namespace iris {

namespace drivers {

class Connection;
class Driver;

/**
 * Represents a concrete sensor instance communicating via a Connection object
 */
class SENSORAPI Sensor {

protected:

    /**
     * Associated Connection instance
     */
    Connection& connection;

    /**
     * UIP address
     */
    int uipAddress;

    /**
     * Constructor.
     * Initializes a new Sensor instance for the given Connection
     *
     * @param connection Associated Connection instance
     * @param address Sensor address without driver prefix
     */
    Sensor(Connection& connection, const std::string& address);

    /**
     * Destructor
     */
    virtual ~Sensor();

    friend class Connection;

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
     * Returns the UIP address. The UIP address is the number after the hash sign in a URL.
     * @return UIP address
     * @see setUipAddress
     */
    int getUipAddress(void) const;
    
    /**
     * @brief setUipAddress Changes the UIP address. The UIP address is the number after the hash sign in a URL.
     * @param uipAddress
     * @note If the UIP changes, it must be updated, otherwise messages will not be received and will be discarded.
     * @note The UIP address can change on grouping or ungrouping of sensors. Direct configuration of the UIP is another possibility.
     * @see getUipAddress
     * @see Dist500::setUipAddress
     */
    void setUipAddress(unsigned int uipAddress);

    /**
     * Extracts the UIP address from an address (separated by #). Returns 0 if none was found.
     *
     * @param addr Sensor address
     *
     * @return UIP address in range (1-255). Returns 0 if none was found.
     */
    static int extractUipAddress(const std::string addr);

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
     * Receives an incoming message using the mailbox
     *
     * @param level UIP level (0..2)
     * @param timeoutMs Timeout in milliseconds
     *
     * @return Received UipMessage instance when succeeded or <code>null</code>
     *         if timeout has occured
     */
    UipMessage* receiveMessage(const int level, int timeoutMs);

    /**
     * Mailbox for incoming messages
     */
    MultiMailBox mailBox;

    /**
     * Dispatches an incoming message.
     * The message is first routed through the dispatch callback (if any).
     * Otherwise, it is directly put into the mailbox.
     *
     * @param level UIP level (0..2)
     * @param message Message to be delivered
     */
    virtual void dispatchMessage(const int level, const UipMessage* message);

    /**
     * Message handler signature for message dispatching
     *
     * @param sensor Sensor instance
     * @param userData User-defined additional parameter
     * @param level UIP level (0..2)
     * @param message The message to be delivered
     *
     * @return <code>true</code> if message has been processed by the callback,
     *         <code>false</code> otherwise
     *
     * @note When a dispatcher callback returns true, it is responsible for its
     *       deletion
     */
    typedef bool (*DispatchCallback)(Sensor& sensor, void* userData,
            const int level, const UipMessage* message);

    /**
     * Sets the dispatcher callback
     *
     * @param userData User-defined additional parameter for the callback
     *        (<code>null</code> disables the callback)
     * @param callback Callback function pointer
     */
    void setDispatchCallback(void* userData, DispatchCallback callback);

    /**
     * Optional dispatcher callback pointer
     */
    DispatchCallback dispatchCallback;

    /**
     * User-defined additional parameter for dispatcher callback
     */
    void *dispatchCallbackUserData;

    iris::synchronization::Mutex& getExclusionGroupMutex(void);

    iris::synchronization::Mutex& getAccessMutex(void);
    
    /**
     * @brief setConnectionAddress Sets a new connection address for this Sensor. Used for DHCP.
     */
    void setConnectionAddress(const std::string& newAddress);

}; // class Sensor

} // namespace drivers

} // namespace iris

#endif // DRIVERS_SENSOR_H
