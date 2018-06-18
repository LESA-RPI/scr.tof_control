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

#ifndef DIST500_DOORCONTROLLER_H
#define DIST500_DOORCONTROLLER_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/Dist500Base.h"
#include "iris/dist500/DoorStateSource.h"
#include "iris/dist500/HallSensorStateSource.h"

namespace iris {

namespace dist500 {

/**
 * This class represents the door functionality within the DIST500 sensor
 * @see getDoorState
 */
class SENSORAPI DoorController: virtual public Dist500Base, public DoorStateSource, public HallSensorStateSource {

public:
    typedef enum {
        /**
         * Hall sensor status is off and the hardware has no effect
         */
        ForcedOff = 0,
        /**
         * Hall sensor status is on and the hardware has no effect
         */
        ForcedOn = 1,
        /**
         * Hardware has effect
         */
        Neutral = 2,

        __FirstUnusedManualHallSensorStatus
    } ManualHallSensorStatus;

    /**
     * Constructor
     *
     * @param sensor Sensor reference from driver framework
     */
    DoorController(iris::drivers::Sensor& sensor);

    /**
     * Sets the state of a door
     *
     * @param functionArea Functionarea number
     * @param doorNumber Door number
     * @param leftState Opening state of left door (0..100 percent)
     * @param rightState Opening state of right door (0..100 percent)
     *
     * @return Operation result
     * @see getDoorState
     */
    SENSOR_RESULT setDoorState(unsigned short functionArea, unsigned short doorNumber, unsigned char leftState, unsigned char rightState);

    /**
     * Retrieves a door state
     *
     * @param functionArea Functionarea number
     * @param doorNumber Door number
     * @param leftState Buffer for opening state of left door (0..100 percent)
     * @param rightState Buffer for opening state of right door (0..100 percent)
     *
     * @return Operation result
     * @see setDoorState
     */
    SENSOR_RESULT getDoorState(unsigned short functionArea, unsigned short doorNumber, unsigned char &leftState, unsigned char &rightState);

    /**
     * Sets the state of the hall sensor
     *
     * @param state A manually set hall sensor state (ManualHallSensorStatus)
     *
     * @return Operation result
     * @see getHallSensorState
     */
    SENSOR_RESULT setHallSensorState(ManualHallSensorStatus state);

    /**
     * Retrieves the hall sensor state
     *
     * @param state output char reference for the hall sensor state
     *
     * @return Operation result
     * @see setHallSensorState
     */
    SENSOR_RESULT getHallSensorState(unsigned char &state);

    /**
     * Enable the hall sensor
     *
     * @return Operation result
     * @see disableHallSensor
     */
    SENSOR_RESULT enableHallSensor(void);

    /**
     * Disable the hall sensor
     *
     * @return Operation result
     * @see enableHallSensor
     */
    SENSOR_RESULT disableHallSensor(void);

    /**
     * Get the hall sensor function
     *
     * @param function Reference to receiving the hall sensor function
     *
     * @return Operation result
     * @see setHallSensorFunction
     */
     SENSOR_RESULT getHallSensorFunction(iris::uip::hall_sensor_function& function);

    /**
     * Set the hall sensor function
     *
     * @param function Hall sensor function
     *
     * @return Operation result
     * @see getHallSensorFunction
     */
    SENSOR_RESULT setHallSensorFunction(iris::uip::hall_sensor_function function);

protected:

    /**
     * Callback function for spontaneous messages (sub-command *), here only for
     * D 3.0
     *
     * @param base Dist500Base instance (surrogate for this pointer)
     * @param message Spontaneously received message
     * @see getDoorState
     */
    static void handleSpontaneousDoorMessage(Dist500Base* base, UipMessage* message);

    /**
     * Callback function for spontaneous messages (sub-command *), here only for
     * D 3.1
     *
     * @param base Dist500Base instance (surrogate for this pointer)
     * @param message Spontaneously received message
     * @see getHallSensorState
     */
    static void handleSpontaneousHallSensorMessage(Dist500Base* base, UipMessage* message);

}; // class DoorController

} // namespace dist500

} // namespace iris

#endif // DIST500_DOORCONTROLLER_H
