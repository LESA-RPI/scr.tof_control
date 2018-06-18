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
// ---------------------------------------------------------------------------

#ifndef DIST500_DIST500_H
#define DIST500_DIST500_H

// STL includes
#include <list>
#include <map>
#include <set>

// iris includes
#include "iris/Common.h"
#include "iris/dist500/CountResultSource.h"
#include "iris/dist500/Dist500Base.h"
#include "iris/dist500/FirmwareController.h"
#include "iris/dist500/FpgaController.h"
#include "iris/dist500/LoggerController.h"
#include "iris/dist500/Picture.h"
#include "iris/dist500/PictureSource.h"
#include "iris/dist500/RegisterValuesSource.h"
#include "iris/dist500/DoorStateSource.h"
#ifdef APIBUILD
    #include "UipTypes.h"
#else
    #include "../UipTypes.h"
#endif
#include "iris/dist500/DoorController.h"
#include "iris/dist500/CounterController.h"
#include "iris/dist500/InstallationModeController.h"

namespace iris {

namespace dist500 {

/**
 * Represents a DIST500 sensor
 */
class SENSORAPI Dist500: public InstallationModeController, public FpgaController, public FirmwareController, public CounterController, public DoorController, public LoggerController {

    // TODO terminalcontroller, filesystemcontroller
    // TODO extract configurationcontroller ?
    // TODO PerformanceSource/Sink, LoggerSource/Sink, RegisterSource/Sink

protected:

    /**
     * Static callback for incoming messages in "streaming" installation mode
     *
     * @param sensor Sensor instance
     * @param userData User-defined additional parameter
     * @param level UIP message level
     * @param message UIP message
     *
     * @return <code>true</code> if message has been processed, <code>false</code>
     *         otherwise
     */
    static bool dispatchCallback(iris::drivers::Sensor& sensor, void* userData,
            const int level, const UipMessage* message);

public:

    /**
     * Constructor
     *
     * @param sensor
     */
    Dist500(iris::drivers::Sensor& sensor);

    /**
     * Destructor
     */
    virtual ~Dist500();

    /**
     * Orders the sensor to restart which takes a couple of seconds to become fully operational. Also called "soft reboot" whereas a "hard reboot" is made by powering off and on.
     *
     * @return Operation result
     */
    SENSOR_RESULT resetDsp(void);

    /**
     * Sets the status LED mode (on, off or blinking behaviour).  This is not related to the infrared illumination LEDs.
     * @param mode Is a iris::uip::status_led_work_mode
     * @return 
     * @see getStatusLedMode
     */
    SENSOR_RESULT setStatusLedMode(const iris::uip::status_led_work_mode mode);

    /**
     * Returns the status LED mode. This is not related to the infrared illumination LEDs.
     * @param mode Output parameter containing an iris::uip::status_led_work_mode
     * @return 
     * @see setStatusLedMode
     */
    SENSOR_RESULT getStatusLedMode(iris::uip::status_led_work_mode &mode);

    /**
     * Returns the sensor revision code
     * @param revisionCode Output parameter
     * @return 
     * @see SensorInfo
     */
    SENSOR_RESULT getSensorRevisionCode(unsigned short& revisionCode);
    
    typedef std::set<iris::uip::firmware_feature_type> FirmwareFeatureSet;
    
    /**
     * Returns a set of supported firmware features. See enumeration firmware_feature_type. Some older firmwares do not support this message. See checkSupportForMessage().
     * 
     * @param featureSet
     * @return Operation success
     */
    SENSOR_RESULT getFirmwareFeatures(FirmwareFeatureSet& featureSet);

    /**
     * Stops the picture acquisition
     *
     * @return Operation result
     * 
     * @see startPictureAcquisision
     * @deprecated the typographic error is also left for backwards (compile) compatibility.
     */
    SENSOR_RESULT stopPictureAcquisision(void);

    /**
     * Starts the picture acquisition
     *
     * @return Operation result
     * @see stopPictureAcquisision
     * @deprecated the typographic error is also left for backwards (compile) compatibility.
     */
    SENSOR_RESULT startPictureAcquisision(void);

    /**
     * Checks if picture acquisition is running
     *
     * @return Operation result
     * @deprecated the typographic error is also left for backwards (compile) compatibility.
     */
    SENSOR_RESULT isPictureAcquisitionRunning(bool& running);


    /**
     * Switches the automatic exposure control on
     *
     * @return Operation result
     * @see disableExposureControl
     */
    SENSOR_RESULT enableExposureControl(void);

    /**
     * Switches the automatic exposure controll off
     *
     * @return Operation result
     * @see enableExposureControl
     */
    SENSOR_RESULT disableExposureControl();

    typedef std::list<unsigned long> RegisterList;
    typedef std::map<unsigned long, unsigned long> RegisterValueMap;

    /**
     * Gets a list with DSP registers useful for introspection
     * 
     * @param registerList
     * @param registerValueMap
     * @return 
     */
    SENSOR_RESULT getDspRegisters(const RegisterList& registerList, RegisterValueMap& registerValueMap);

    /**
     * Sends a test message with a number which is expected to be returned in the reply payload; number can be reset with resetCommunicationTestCounter
     * 
     * @param number
     * @param expectedNumber
     * @param testDataLen
     * @param payload
     * @return 
     */
    SENSOR_RESULT sendCommunicationTestMessage(const unsigned long number,
                                               unsigned long& expectedNumber,
                                               const unsigned short testDataLen,
                                               const char* const payload);

    /**
     * Used with sendCommunicationTestMessage to reset the counter in the sensor.
     * 
     * @return Operation result
     */
    SENSOR_RESULT resetCommunicationTestCounter(void);

protected:

    /**
     * This class controls automatic enabling/disabling of picture actuisition
     * during certain operations (ie firmware updates). Follows the RAII pattern.
     */
    class PictureAcquisitionGuard {

        /**
         * Dist500 instance for which the guard works
         */
        Dist500* protegee;

        /**
         * Flag containing the acquisitions state before the operation
         */
        bool wasRunning;

    public:

        /**
         * Constructor
         *
         * @param protegee Dist500 instance to be protected
         */
        PictureAcquisitionGuard(Dist500* protegee);

        /**
         * Destructor
         */
        virtual ~PictureAcquisitionGuard();

    };

}; // class Dist500

} // namespace dist500

} // namespace iris

#endif // DIST500_DIST500_H
