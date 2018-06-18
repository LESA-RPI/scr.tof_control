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

#ifndef SOCKETCANIMPLEMENTATION_H
#define SOCKETCANIMPLEMENTATION_H

#if defined(__linux__) && !defined(IRIS_DISABLE_SOCKETCAN)

// Socket CAN implementation of our CAN driver.
//
// BAUD RATE NOTES
//
// There is no way to set the baud rate via SocketCAN, so a supported baud rate
// must be configured for the interface.
// Currently the Irma Matrix supports 125000 baud.
// Example shell commands (sudo may be necessary):
// ip link set can0 down
// ip link set can0 type can bitrate 125000
// ip link set can0 up
//
// Permanent configuration of bitrate is possible in /etc/network/interfaces

#include <string>

#include "CanDriver.h"
#include "CanDriverImplementation.h"

#include "iris/utilities/MailBox.h"
#include "iris/synchronization/Event.h"

namespace iris {

namespace drivers {

namespace can {

class SENSORAPI SocketCanImplementation : public CanDriverImplementation
{
public:
    static const std::string& ImplementationOptionValue;

    SocketCanImplementation(CanDriver& driver);
    virtual ~SocketCanImplementation();
    
    void startup(const int busSpeed);

    void shutdown(void);

    void sendFrame(CanDriver::CanFrame& frame);
    
    class SocketCanErrorCondition: public CanDriver::CanErrorCondition {
    public:
        int apiErrno;
        //bool apiErrAtSocket;
        bool apiErrAtSelect;
        bool apiErrAtRead;
        bool apiErrAtWrite;
        bool timeout;
        bool missingAck;
        bool busOff;
        bool busError;
        bool restarted;
        // See linux/can/error.h for definitions data0 - data4
        int data0_errorArbitration;
        int data1_errorStatus;
        int data2_errorInProtocolType;
        int data3_errorInProtocolLocation;
        int data4_errorAtTransceiver;
    };
    
    friend class CanDriver;// TODO needed?
    
    static CanDriverImplementation* makeInstance(CanDriver& driver);
    
protected:
    std::string m_interfaceName;

    int m_socketHandle;
    
    iris::synchronization::Event m_startedEvent;
    
    boost::thread* m_receiveThread;
    boost::thread* m_forwardThread;
    
    iris::utilities::MailBox m_mailBox;
    
    bool m_finished;
    
    bool isFinished() { return m_finished; }
    
    int getSocketHandle() { return m_socketHandle; }
    
    bool waitForStart(int timeoutMs);
    
    void signalStart(void);
    
    void putToMailBox(const CanDriver::CanFrame& frame);

    void forwardMailBoxFrames(void);
    
    /**
     * Implements a CAN frame reception thread
     */
    class ReceiveThread {

        /**
         * Holds the corresponding CanDriver instance
         */
        SocketCanImplementation* m_driver;
        
        int m_socketHandle;

    public:

        /**
         * Constructor
         *
         * @param md Corresponding CanDriver instance
         */
        ReceiveThread(SocketCanImplementation* m_driver);

        /**
         * Execution method (boost functor)
         */
        void operator()();

    }; // class ReceiveThread

    /**
     * Implements a CAN frame forwarding thread
     */
    class ForwardThread {

        /**
         * Holds the corresponding CanDriver instance
         */
        SocketCanImplementation* m_driver;

    public:

        /**
         * Constructor
         *
         * @param md Corresponding CanDriver instance
         */
        ForwardThread(SocketCanImplementation* m_driver);

        /**
         * Execution method (boost functor)
         */
        void operator()();

    }; // class ForwardThread
};

}

}

}

#endif // #ifdef __linux__

#endif // SOCKETCANIMPLEMENTATION_H
