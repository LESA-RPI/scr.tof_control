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

#ifndef DRIVERS_CAN_CANDRIVER_H
#define DRIVERS_CAN_CANDRIVER_H

// STL includes
#include <map>

// boost includes
#include <boost/thread/condition.hpp>

// iris includes
#include "iris/drivers/Driver.h"

// internal class forwards
#ifndef DONT_DECLARE_UIPMESSAGE
    class UipMessage;
#endif

namespace iris {

namespace drivers {

namespace can {

class CanDriverImplementation;

/**
 * Implements a CAN driver
 */
class SENSORAPI CanDriver: public iris::drivers::Driver {

public:

    /**
     * Holds a list containing the scanned sensor addresses
     */
    mutable AddressList scanList;

    /**
     * Flag indicating whether a device scan is active
     */
    mutable bool scanInProgress;

public:

    /**
     * Constructor
     */
    CanDriver();

    /**
     * Destructor
     */
    virtual ~CanDriver();

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

    static const std::string& BusSpeedOptionName;

    static const std::string& ImplementationOptionName;

    static const std::string& CanIrmaServicePcOptionName;
    
    static const std::string& CanInterfaceOptionName;

//protected:

    typedef enum {
        DataFrame,
        RemoteFrame,
        ErrorFrame
    } FrameType;

    typedef struct {
        FrameType frameType;
        bool extended;
        unsigned long identifier;
        unsigned char dataLength;
        unsigned char data[8];
    } CanFrame;

    class CanErrorCondition {
    public:
        virtual ~CanErrorCondition();
    };

    void canReceptionCallback(const CanFrame& frame);

    void canErrorConditionCallback(const CanErrorCondition& condition);

    friend class CanDriverImplementation;

    CanDriverImplementation* implementation;

    boost::condition_variable event;
    bool started;

    bool canIrmaServicePc;

    typedef std::list<CanFrame*> CanFrameList;

    CanFrameList splitUipMessage(int level, const std::string& addr, UipMessage* uipMessage, const bool broadcast) const;

    void sendMessage(const int level, const std::string& addr, const UipMessage* message, const bool broadcast) const;

    class Recombiner {
    protected:
        CanDriver& driver;
        int addr;
        int expectedPayloadLen;
        int processedPayloadLen;
        int expectedFrameCount;
        int processedFrameCount;
        char buffer[2000];
        int bufferPos;
        bool active;
        int level;
        void reset(void);
    public:
        Recombiner(CanDriver& driver, const int addr);
        void processPartialFrame(const CanFrame& frame);
    };

    typedef std::map<int, Recombiner*> RecombinerMap;

    RecombinerMap recombiners;

    void uipReceptionCallback(const int level, const int addr, UipMessage* message);

    bool supportsParallelAccess(void) const;

    typedef void (*RAW_CAN_DEBUG_CALLBACK) (void* userData, const CanFrame& frame);

    typedef void (*RAW_CAN_ERROR_CALLBACK) (void* userData, const CanErrorCondition& condition);

    typedef void (*CAN_IRMA_DEBUG_CALLBACK) (void* userData, const CanFrame& frame, const int code, const int dest, const int addr);

    typedef enum { FrameTooShortError, LastFrameIncomplete, InvalidPayloadLen, UnexpectedSubFrameNumber,
                   FrameCountOrTotalLenMismatch, SubFrameProcessed, UipFrameCompleted} UipCanIrmaRecombinerStatus;

    typedef void (*UIP_CAN_IRMA_DEBUG_CALLBACK) (void* userData, const CanFrame& frame, const UipCanIrmaRecombinerStatus status);

    void setRawCanDebugListener(RAW_CAN_DEBUG_CALLBACK listener, void* userData = 0);

    void setRawCanErrorListener(RAW_CAN_ERROR_CALLBACK listener, void* userData = 0);

    void setCanIrmaDebugListener(CAN_IRMA_DEBUG_CALLBACK listener, void* userData = 0);

    void setUipCanIrmaDebugListener(UIP_CAN_IRMA_DEBUG_CALLBACK listener, void* userData = 0);

    void clearRawCanDebugListener(void);

    void clearRawCanErrorListener(void);

    void clearCanIrmaDebugListener(void);

    void clearUipCanIrmaDebugListener(void);

    typedef CanDriverImplementation* (*IMPLEMENTATION_FACTORY_FUNCTION) (CanDriver& driver);

    typedef std::map<std::string, IMPLEMENTATION_FACTORY_FUNCTION> ImplementationFactoryMap;

    static void registerCanDriverImplementation(const std::string& name, IMPLEMENTATION_FACTORY_FUNCTION factoryFunction);

protected:

    static ImplementationFactoryMap implementationFactoryMap;

    RAW_CAN_DEBUG_CALLBACK rawCanDebugListener;

    CAN_IRMA_DEBUG_CALLBACK canIrmaDebugListener;

    UIP_CAN_IRMA_DEBUG_CALLBACK uipCanIrmaDebugListener;

    RAW_CAN_ERROR_CALLBACK rawCanErrorListener;

    void* rawCanDebugListenerUserData;

    void* rawCanErrorListenerUserData;

    void* canIrmaDebugListenerUserData;

    void* uipCanIrmaDebugListenerUserData;

}; // class CanDriver

} // namespace can

} // namespace drivers

} // namespace iris

#endif // DRIVERS_CAN_CANDRIVER_H
