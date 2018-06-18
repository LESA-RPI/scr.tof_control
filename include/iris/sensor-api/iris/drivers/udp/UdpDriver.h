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

#ifndef DRIVERS_UDP_UDPDRIVER_H
#define DRIVERS_UDP_UDPDRIVER_H

// workaround for win32: needs to be first include
#if defined(__WIN32) || defined(_WIN32)
#include <winsock2.h>
#endif

// boost includes
#include <boost/asio.hpp>
//#include <boost/array.hpp>

// iris includes
#include "iris/drivers/Driver.h"
#include "iris/synchronization/Mutex.h"
#include "iris/threads/Thread.h"

namespace iris {

namespace utilities {

class LogEntryCache;
class LogCategory;

}

namespace drivers {

namespace udp {

/**
 * Implements an UIP-over-UDP driver
 */
class SENSORAPI UdpDriver: public iris::drivers::Driver {

public:

    /**
     * boost ioservice instance
     */
    boost::asio::io_service *ios_;

    /**
     * boost socket instance
     */
    boost::asio::ip::udp::socket *socket_;

    /**
     * boost remote endpoint instance
     */
    boost::asio::ip::udp::endpoint remote_endpoint_;

    /**
     * Raw (bytes) reception buffer for UDP datagrams
     */
    char receiveBuffer[2000];

    /**
     * Holds a list containing the scanned sensor addresses
     */
    mutable AddressList scanList;

    class ReceiveThread;

    /**
     * Holds the receive thread instance
     */
    mutable ReceiveThread* t;

    typedef std::list<boost::asio::ip::address_v4> BroadcastAddressList;

    BroadcastAddressList broadcastAddresses;

    mutable SCAN_CALLBACK scanCallback;

    mutable void * scanUserData;

    unsigned char senderAddress;

public:

    /**
     * Constructor
     */
    UdpDriver();

    /**
     * Destructor
     */
    virtual ~UdpDriver();

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
     * Initiates a new receive process on the socket
     */
    void request_receive(void);

    /**
     * Callback method for successful or failed reception processes
     *
     * @param error Success/error code
     * @param bytes_transferred Byte size of received packet
     */
    void handle_receive(const boost::system::error_code& error, std::size_t bytes_transferred);

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
    class ReceiveThread: public iris::threads::Thread {

    /**
     * Holds the corresponding UdpDriver instance
     */
    UdpDriver* md;

    public:

        /**
         * Constructor
         *
         * @param md Corresponding UdpDriver instance
         */
        ReceiveThread(UdpDriver* md);

        /**
         * Execution method
         */
        unsigned int execute(void);

    }; // class ReceiveThread

    iris::synchronization::Event event;
    iris::synchronization::Mutex mutex;
    bool started;

    bool waitForStart(int timeoutMs);
    void signalStart(void);

    static const std::string& AdditionalNetworksOptionName;

    static const std::string& AdditionalHostsOptionName;
    
    static const std::string& TimeoutOffsetOptionName;

    static const std::string& TimeoutFactorOptionName;

    static const std::string& AutoTimeoutsOptionName;

    static const std::string& BindAddressOptionName;

    static const std::string& BindPortOptionName;

    static const std::string& SuppressLocalSubnetBroadcastsOptionName;

    static const std::string& SuppressGlobalBroadcastOptionName;

    bool autoTimeouts;

    /**
     * Sets the UIP address of the sender.
     *
     * @param addr UIP address between 240 and 254.
     */
    void setSenderAddress(unsigned char addr);

    static volatile bool finished;

    mutable iris::synchronization::Mutex sendMutex;

    mutable iris::synchronization::Mutex receiveMutex;

    static const std::string& Mnemonic;

    static const std::string& EnableLoggingOptionName;

    static const std::string& LogfileNameOptionName;

protected:

    std::string getExclusionGroupName(void) const;

    mutable iris::utilities::LogEntryCache* logCache;

    mutable iris::utilities::LogCategory* rxCategory;

    mutable iris::utilities::LogCategory* txCategory;

    mutable iris::utilities::LogCategory* txErrCategory;

    void log(utilities::LogCategory *category, const void* data, const unsigned short len) const;

}; // class UdpDriver

} // namespace udp

} // namespace drivers

} // namespace iris

#endif // DRIVERS_UDP_UDPDRIVER_H
