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

#ifndef DRIVERS_SERIAL_SERIALDRIVER_H
#define DRIVERS_SERIAL_SERIALDRIVER_H

// workaround for win32: needs to be first include
#if defined(__WIN32) || defined(_WIN32)
#include <winsock2.h>
#endif

// boost includes
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

// iris includes
#include "iris/drivers/Driver.h"
#include "iris/synchronization/Event.h"
#include "iris/synchronization/Mutex.h"

namespace iris {

namespace drivers {

namespace serial {

// internal class forward
class UipCommunicator;

class SENSORAPI SerialDriver: public iris::drivers::Driver {

public:

    /**
     * Holds the UIP communicator object
     */
    UipCommunicator* communicator;

    /**
     * boost ioservice instance
     */
    boost::asio::io_service *ios_;

    /**
     * boost port instance
     */
    boost::asio::serial_port *port_;

    /**
     * boost deadline timer instance
     */
    boost::asio::deadline_timer *dlt_;

    /**
     * Raw (bytes) reception buffer for serial datagrams
     */
    char receiveBuffer[2000];

    /**
     * Variable holding the actual reception length
     */
    int receiveLength;

    /**
     * Holds a list containing the scanned sensor addresses
     */
    mutable AddressList scanList;

    /**
     * Defines a list of UIP addresses
     */
    typedef std::list<unsigned char> UipAddressList;

    /**
     * Holds a list containing the scanned gateways' UIP addresses
     */
    mutable UipAddressList gateways;

    /**
     * Holds a list of gateway UIP addresses to be tested during scan
     */
    UipAddressList gatewaysOfInterest;

    /**
     * Flag indicating whether the gateway scan is stopped at the first
     * unsuccessful address
     */
    bool stopScanAtTimeout;

    /**
     * Holds the receive thread instance
     */
    mutable boost::thread* t;

    typedef std::list<boost::asio::ip::address_v4> BroadcastAddressList;

    BroadcastAddressList broadcastAddresses;

    iris::synchronization::Event* scanEvent;

    unsigned char senderAddress;

public:

    static const std::string PortNameOptionName;

    static const std::string IbisSwitchOptionName;

    static const std::string IbisSpeedOptionName;

    static const std::string IbisBvgOptionName;

    static const std::string Ibis8n1OptionName;

    /**
     * Constructor
     */
    SerialDriver();

    /**
     * Destructor
     */
    virtual ~SerialDriver();

    /**
     * Returns the list of all sensors addresses that can currently be found
     *
     * @return Address list (without URL prefix and :// separator)
     */
    AddressList performAddressScan(void* userData = 0, SCAN_CALLBACK callback = 0) const;

    /**
     * Sends the given message
     *
     * @param level UIP level (0..2)
     * @param addr Sensor address
     * @param message Message to be sent
     */
    void sendMessage(const int level, const std::string& addr,
            const UipMessage* message) const;

    /**
     * Sends the given message in broadcast mode
     *
     * @param level UIP level (0..2)
     * @param message Message to be sent
     */
    void sendBroadcastMessage(const int level, const UipMessage* message) const;

    /**
     * Initiates a new receive process on the port
     */
    void request_receive(void);

    /**
     * Callback method for successful or failed reception processes
     *
     * @param error Success/error code
     * @param bytes_transferred Byte size of received packet
     */
    void handle_receive(const boost::system::error_code& error,
            std::size_t bytes_transferred);

    /**
     * Initializes the driver
     */
    void startupDriver(void);

    /**
     * Deinitializes the driver
     */
    void shutdownDriver(void);

    /**
     * Implements a reception thread
     */
    class ReceiveThread {

    /**
     * Holds the corresponding SerialDriver instance
     */
    SerialDriver* md;

    public:

        /**
         * Constructor
         *
         * @param md Corresponding UdpDriver instance
         */
        ReceiveThread(SerialDriver* md);

        /**
         * Execution method (boost functor)
         */
        void operator()();

    }; // class ReceiveThread

    iris::synchronization::Mutex mutex;
    iris::synchronization::Event started;

    bool waitForStart(int timeoutMs);
    void signalStart(void);

    void sendIbisSwitch(unsigned char gwAddr) const;

    /**
     * Sets the UIP address of the sender.
     *
     * @param addr UIP address between 240 and 254.
     */
    void setSenderAddress(unsigned char addr);

    protected:

    void messageCallback(int level, const std::string& addr, UipMessage* message);

    friend class UipCommunicator;

    static volatile bool finished;

    bool supportsParallelAccess(void) const;

}; // class SerialDriver

} // namespace serial

} // namespace drivers

} // namespace iris

#endif // DRIVERS_SERIAL_SERIALDRIVER_H
