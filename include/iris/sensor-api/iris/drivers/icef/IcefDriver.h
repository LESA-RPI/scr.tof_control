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

#ifndef DRIVERS_ICEFDRIVER_H
#define DRIVERS_ICEFDRIVER_H

// boost includes
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>

// iris includes
#include "iris/drivers/Driver.h"
#include "iris/threads/Thread.h"
#include "iris/synchronization/Event.h"
#include "iris/synchronization/Mutex.h"

namespace iris {

namespace drivers {

namespace icef {

#pragma pack(1)

typedef struct {
    unsigned char receiverMac[6];
    unsigned char senderMac[6];
    int payloadLength;
    char payloadData[1400];
} IcefFrame;

#pragma pack()

class WritingIcefPipeClient;
class ReadingIcefPipeClient;

/**
 * Implements an UIP-over-ICEF driver
 */
class SENSORAPI IcefDriver: public iris::drivers::Driver {

public:

    /**
     * Raw (bytes) reception buffer for ICEF datagrams
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

    class ReceiveThread;

    /**
     * Holds the receive thread instance
     */
    mutable ReceiveThread* recThread;

    unsigned char senderAddress;

public:

    /**
     * Constructor
     */
    IcefDriver();

    /**
     * Destructor
     */
    virtual ~IcefDriver();

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
     * Holds the corresponding IcefDriver instance
     */
    IcefDriver* md;

    public:

        /**
         * Constructor
         *
         * @param md Corresponding IcefDriver instance
         */
        ReceiveThread(IcefDriver* md);

        /**
         * Execution method (boost functor)
         */
        unsigned int execute(void);

    }; // class ReceiveThread

    iris::synchronization::Event event;
    iris::synchronization::Mutex mutex;

    bool waitForStart(int timeoutMs);
    void signalStart(void);

    /**
     * Sets the UIP address of the sender.
     *
     * @param address UIP address between 240 and 254.
     */
    void setSenderAddress(unsigned char address);

protected:

    //friend class EthernetDriverImplementation;

    void receptionCallback(const IcefFrame& frame);

    //EthernetDriverImplementation* impl;

    WritingIcefPipeClient *wipc;
    ReadingIcefPipeClient *ripc;

    void prepareServices(void);

    std::string getExclusionGroupName(void) const;

    bool supportsParallelAccess(void) const;

}; // class IcefDriver

} // namespace icef

} // namespace drivers

} // namespace iris

#ifdef DYNLIB

// Standard C driver DLL interface
extern "C" {

/**
 * Returns the magic number to identify a driver
 *
 * @return Magic number (0x53495249)
 */
int getMagicNumber(void);

/**
 * Creates a driver instance
 *
 * @return Driver (here: IcefDriver) instance
 */
iris::drivers::Driver* createInstance(void);

} // extern "C"

#endif

#endif // DRIVERS_ICEFDRIVER_H
