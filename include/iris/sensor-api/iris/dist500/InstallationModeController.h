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

#ifndef DIST500_INSTALLATIONMODECONTROLLER_H
#define DIST500_INSTALLATIONMODECONTROLLER_H

// STL includes
#include <set>

// iris includes
#include "iris/Common.h"
#include "iris/dist500/Dist500Base.h"
#include "iris/dist500/PictureSource.h"
#include "iris/dist500/RegisterValuesSource.h"
#include "iris/synchronization/Mutex.h"
#include "iris/synchronization/Event.h"
#include "iris/threads/Thread.h"
#include "iris/dist500/DebugDataSource.h"

namespace iris {

namespace dist500 {

/**
 * Represents the DIST500's installation mode facility, which is used for live picture streaming from a sensor.
 */
class SENSORAPI InstallationModeController: public virtual Dist500Base, public PictureSource, public RegisterValuesSource, public DebugDataSource {

protected:

    /**
     * Installation mode termination event
     */
    iris::synchronization::Event terminationEvent;

    /**
     * Mutex for installation mode parameters
     */
    iris::synchronization::Mutex callbackMutex;

    /**
     * Buffer for pixel values
     */
    unsigned short pixelBuffer[1000];

    /**
     * Buffer for Picture instance
     */
    Picture* pictureBuffer;

    /**
     * Holds the last picture number in installation mode
     */
    unsigned long lastPictureNumber;

    /**
     * Holds the timestamp of the last picture in installation mode
     */
    unsigned long long lastTimestamp;

    /**
     * Holds the current installation mode picture count
     */
    unsigned int pictureCount;

    /**
     * Holds the installation mode picture limit
     */
    unsigned int maxPictures;

    /**
     * Holds the installation mode time limit
     */
    unsigned long long maxTime;

    typedef std::set<InstallationModeController*> InstModeSensorsSet;

    static InstModeSensorsSet runningSensors;

    class RequestThread: public iris::threads::Thread {

    public:

        RequestThread();
        virtual ~RequestThread();

        unsigned int execute(void);

    };

    static RequestThread* requestThread;

    static iris::synchronization::Mutex requestMutex;

    static void registerRunningSensor(InstallationModeController* sensor);

    static void unregisterRunningSensor(InstallationModeController* sensor);

    static bool isSensorInUse(InstallationModeController* sensor);

    SENSOR_RESULT continueInstallationMode(void);

    static InstModeSensorsSet stoppingSensors;

    static void registerStoppingSensor(InstallationModeController* sensor);

    bool useInstallationModeRetrigger;

public:

    /**
     * Callback for installation mode status
     *
     * @param userData User-defined additional parameter
     * @param running Flag indicating the status (<code>true</code> =
     running, <code>false</code> = stopped)
     */
    typedef void (*STATUS_CALLBACK)(void* userData, bool running);

    /**
     * Callback for installation mode progress
     *
     * @param userData User-defined additional parameter
     * @param pictureNumber Picture number since start
     * @param maxPictures Maximum number of picture (0 = unlimited)
     * @param timestamp Picture timestamp
     * @param elapsedTime Elapsed time since start
     * @param maxTime Maximum time (0 = unlimited)
     */
    typedef void (*PROGRESS_CALLBACK)(void* userData, long pictureNumber,
            long maxPics, unsigned long long elapsedTime,
            unsigned long long maxTime);

    /**
     * Constructor
     *
     * @param sensor Sensor reference from drifver framework
     */
    InstallationModeController(iris::drivers::Sensor& sensor);

    /**
     * Destructor
     */
    virtual ~InstallationModeController();

    /**
     * Installation mode type, refers to image format that is streamed.
     */
    typedef enum {

        /**
         * Distance and amplitude, 12/16 bits
         */
        Full16,

        /**
         * Distance only, 12/16 bits
         */
        Distance16,

        /**
         * Amplitude only, 12/16 bits
         */
        Amplitude16,

        /**
         * Distance and amplitues, 8 bits
         */
        Full8,

        /**
         * Distance only, 8 bits
         */
        Distance8,

        /**
         * Amplitude only, 8 bits
         */
        Amplitude8

    } InstallationModeType;

    /**
     * Holds the current installation mode type
     */
    InstallationModeType instModeType;

    /**
     * Starts the installation mode
     *
     * @param type
     * @param userData
     * @param statusCallback
     * @param progressCallback
     * @param maxPictures Number of pictures after which installation mode will
     *        auto-stop (0 = no limit)
     * @param maxTime Time in ms after which installation mode will auto-stop
     *        (0 = no limit)
     *
     * @return Operation result
     * 
     * @note At most one of maxPictures and maxTime may be non-zero, but not both !
     * @see disableInstallationMode
     */
    SENSOR_RESULT enableInstallationMode(InstallationModeType type, void* userData,
            STATUS_CALLBACK statusCallback,
            PROGRESS_CALLBACK progressCallback,
            unsigned int maxPictures, unsigned long long maxTime);

    /**
     * Terminates a running installation mode
     *
     * @return Operation result
     * @see enableInstallationMode
     */
    SENSOR_RESULT disableInstallationMode(void);

    /**
     * Waits for termination of installation mode
     *
     * @param timeoutMs Timeout in milliseconds
     *
     * @return Result (<code>true</code>Termination reached within timeout,
     *         <code>false</code> otherwise
     */
    bool waitForInstallationModeEnd(int timeoutMs);

    SENSOR_RESULT singleShot(unsigned long &pictureNumber,
                             unsigned long long &timestamp, unsigned short* buffer);

    /**
     * Enables "Testride mode", Testride is an internal iris tool.
     * @return 
     * @see disableTestrideMode
     */
    SENSOR_RESULT enableTestrideMode(void);

    /**
     * Disables "Testride mode"
     * @return 
     * @see enableTestrideMode
     */
    SENSOR_RESULT disableTestrideMode(void);

    typedef std::set<iris::uip::ushort> InstallationModeRegisterSet;

    bool setInstallationModeRegisterSet(const InstallationModeRegisterSet& regs);

    void disableInstallationModeRetrigger(void);

    void enableInstallationModeRetrigger(void);

    class DataSourceInfo {
        int sourceId;
        std::string name;
        int maxDataSize;
    public:
        DataSourceInfo(const int sourceId, const std::string& name, const int maxDataSize);
        DataSourceInfo();
        DataSourceInfo(const DataSourceInfo& other);
        DataSourceInfo& operator = (const DataSourceInfo& other);
        int getSourceId(void) const;
        std::string getName(void) const;
        int getMaxDataSize(void) const;
    };

    typedef std::list<DataSourceInfo> DataSourceInfoList;

    SENSOR_RESULT listDebugDataSources(DataSourceInfoList& sources);

    typedef enum { NotifyOnChange = 1, NotifyAtTimeIntervals = 2, NotifyAlways = 4, NotifyImmediately = 8 } NotificationFlags;

    class DataSourceSelector {
        int sourceId;
        bool enabled;
        int notificationFlags;
    public:
        DataSourceSelector(int sourceId, bool enabled, int flags);
        int getSourceId(void) const;
        bool isEnabled(void) const;
        int getNotificationFlags(void) const;
    };

    typedef std::list<DataSourceSelector> DataSourceSelectorList;

    SENSOR_RESULT selectDebugDataSources(const DataSourceSelectorList &requestedSources);

    SENSOR_RESULT selectDebugDataSources(const DataSourceSelectorList &requestesSources, DataSourceSelectorList& knownSources);

protected:

    /**
     * Installation mode status callback
     */
    STATUS_CALLBACK statusCallback;

    /**
     * Installation mode progress callback
     */
    PROGRESS_CALLBACK progressCallback;

    /**
     * User-defined additional parameter for installation mode callback
     */
    void* userData;

    volatile bool instModeRunning;

    /**
     * Callback function for spontaneous messages (sub-command *), here only for
     * P 3.0
     *
     * @param base Dist500Base instance (surrogate for this pointer)
     * @param message Spontaneously received message
     */
    static void handleSpontaneousPictureMessage30(Dist500Base *base, UipMessage *message);

    /**
     * Callback function for spontaneous messages (sub-command *), here only for
     * P 3.1
     *
     * @param base Dist500Base instance (surrogate for this pointer)
     * @param message Spontaneously received message
     */
    static void handleSpontaneousPictureMessage31(Dist500Base *base, UipMessage *message);

    /**
     * Callback function for spontaneous messages (sub-command *), here only for
     * P 3.2
     *
     * @param base Dist500Base instance (surrogate for this pointer)
     * @param message Spontaneously received message
     */
    static void handleSpontaneousPictureMessage32(Dist500Base *base, UipMessage *message);

    /**
     * Calls the new register values callback function
     *
     * @param pictureNumber Picture number (from sensor)
     * @param timestamp Timestamp (from sensor)
     * @param regCount Number of registers
     * @param regNos Array with register numbers
     * @param regVals Array with register values
     */
    void fireRegisterValuesCallback(unsigned long pictureNumber, unsigned long long timestamp, unsigned short regCount, unsigned short* regNos, unsigned short* regVals);

    /**
     * Calls the new picture callback function
     *
     * @param subPicNo Number of current sub-picture (1-based)
     * @param subPicTotal Total sub-pics per cycle
     * @param subPicType Type of sub-picture (D: distance, A: amplitude)
     * @param pictureNumber Picture number (from sensor)
     * @param timestamp Timestamp (from sensor)
     * @param values Pointer to pixel data
     */
    void firePictureCallback(unsigned char subPicNo, unsigned char subPicTotal, char subPicType, unsigned long pictureNumber, unsigned long long timestamp, unsigned short* values);

    /**
     * Disables all callbacks
     */
    void discardCallbacks(void);

    iris::uip::ushort instModeRegCount;

    static const int MaxInstModeRegCount = 32;

    iris::uip::ushort instModeRegNos[MaxInstModeRegCount];

    static void handleSpontaneousDebugDataMessage(Dist500Base* base, UipMessage* message);

    SENSOR_RESULT _listDebugDataSources(DataSourceInfoList& sources, ReceptionFlags& receivedSources);

}; // class InstallationModeController

} // namespace dist500

} // namespace iris

#endif // DIST500_INSTALLATIONMODECONTROLLER_H
