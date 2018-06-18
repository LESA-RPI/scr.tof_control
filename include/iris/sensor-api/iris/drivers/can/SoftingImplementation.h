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


#ifndef DRIVERS_CAN_SOFTINGIMPLEMENTATION_H
#define DRIVERS_CAN_SOFTINGIMPLEMENTATION_H

#ifdef __WIN32
#include <winsock2.h>
#endif

// sorry, guys - Windows only !
#ifndef __WIN32
#warning The Softing CAN driver implementation is only supported on Windows platforms
#endif

// STL includes
#include <map>

// boost forward declaration
namespace boost {
    class thread;
}

// OS dependent includes
#ifdef __WIN32
#include <windows.h>
#endif

// iris includes
#include "iris/sharedlibs/SharedLib.h"
#include "CanDriverImplementation.h"
#include "iris/synchronization/Event.h"
#include "iris/synchronization/Mutex.h"
#include "iris/synchronization/Lock.h"
#include "iris/utilities/MailBox.h"

// 3rd party includes
#ifdef __WIN32
// Softing CAN (windows only)
#include "can.h"
#endif

namespace iris {

namespace drivers {

namespace can {

/**
 * @brief The SoftingImplementation class
 * @note uses canpci.dll or canusb.dll
 */
class SENSORAPI SoftingImplementation: public CanDriverImplementation {

protected:

#ifdef __WIN32
    struct st_canlay2lib functions;

    HANDLE receptionEvent;
#endif

    iris::sharedlibs::SharedLib* softingDll;

    bool finished;

    iris::utilities::MailBox mailBox;

    void putToMailBox(const CanDriver::CanFrame& frame);

    void forwardMailBoxFrames(void);

    /**
     * Implements a CAN frame reception thread
     */
    class ReceiveThread {

        /**
         * Holds the corresponding CanDriver instance
         */
        SoftingImplementation* md;

    public:

        /**
         * Constructor
         *
         * @param md Corresponding CanDriver instance
         */
        ReceiveThread(SoftingImplementation* md);

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
        SoftingImplementation* md;

    public:

        /**
         * Constructor
         *
         * @param md Corresponding CanDriver instance
         */
        ForwardThread(SoftingImplementation* md);

        /**
         * Execution method (boost functor)
         */
        void operator()();

    }; // class ForwardThread

    //iris::synchronization::Mutex mutex;
    iris::synchronization::Event started;

    boost::thread* receiveThread;
    boost::thread* forwardThread;

    bool waitForStart(int timeoutMs);
    void signalStart(void);

    typedef struct _TimingParameters{
        const int presc;
        const int sjw;
        const int tseg1;
        const int tseg2;
        const int sam;
        _TimingParameters(const int presc, const int sjw, const int tseg1, const int tseg2, const int sam);
    } TimingParameters;

    typedef std::map<int, TimingParameters> TimingParametersMap;

    class PrefilledTimingParametersMap: public TimingParametersMap {
    protected:
        void registerParams(const int kbps, const TimingParameters& params);
    public:
        PrefilledTimingParametersMap();
    };

    static PrefilledTimingParametersMap timingParams;

    void checkResult(const int result);

public:

    SoftingImplementation(CanDriver& driver, const std::string& dllName);

    virtual ~SoftingImplementation();

    void startup(const int busSpeed);

    void shutdown(void);

    void sendFrame(CanDriver::CanFrame& frame);

    class SoftingCanErrorCondition: public CanDriver::CanErrorCondition {
    public:
        bool receiveOverrun;
        int receiveFifoLostFrames;
        bool acknowledgeOverrun;
        int transmitFifoLostAcks;
        int transmitFifoLostRemotes;
        int busState;
        int errorState;
    };

}; // class SoftingImplementation

class SENSORAPI SoftingCanUsbImplementation: public SoftingImplementation {

public:

    SoftingCanUsbImplementation(CanDriver& driver);

    static const std::string& ImplementationOptionValue;

    static CanDriverImplementation* makeInstance(CanDriver& driver);

}; // class SoftingCanUsbImplementation

class SENSORAPI SoftingCanPciImplementation: public SoftingImplementation {

public:

    SoftingCanPciImplementation(CanDriver& driver);

    static const std::string& ImplementationOptionValue;

    static CanDriverImplementation* makeInstance(CanDriver& driver);

}; // class SoftingCanPciImplemenation

} // namespace can

} // namespace drivers

} // namespace iris

#endif // DRIVERS_CAN_SOFTINGIMPLEMENTATION_H
