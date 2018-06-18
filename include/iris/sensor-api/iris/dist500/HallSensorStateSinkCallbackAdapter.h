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

#ifndef DIST500_HALLSENSORSTATESINKCALLBACKADAPTER_H
#define DIST500_HALLSENSORSTATESINKCALLBACKADAPTER_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/HallSensorStateSink.h"

namespace iris {

namespace dist500 {

/**
 * Acts as a HallSensorStateSink adapter class which delegates the processNewHallSensorState()
 * event to an external callback function.
 * This allows for integration with objects where subclassing from HallSensorStateSink
 * is impossible or undesired.
 */
class SENSORAPI HallSensorStateSinkCallbackAdapter: public HallSensorStateSink {

public:

    /**
     * Typedef for callback
     *
     * @param userData User-defined additional parameter for callback
     * @param hallSensorState HallSensorState instance with data
     * @param stateIndex countIndex 0-based index of the picture if the total number of
     *        state objects is known, 0 otherwise
     * @param stateIndexCount Total number of state objects (0 if unknown)
     */
    typedef void (*HallSensorStateCallback)(void* userData, HallSensorState* hallSensorState,
                                      unsigned long stateIndex, unsigned long stateIndexCount);

protected:

    /**
     * Pointer to callback function
     */
    HallSensorStateCallback callback;

    /**
     * User-defined additional parameter for callback
     */
    void* userData;

    /**
     * Passes on HallSensorState data to the callback function
     *
     * @param state HallSensorState instance
     * @param stateIndex 0-based index of the picture if the total number of
     *        data objects is known, 0 otherwise
     * @param stateIndexCount Total number of state objects (0 if unknown)
     */
    void processNewHallSensorState(HallSensorState* state, unsigned long stateIndex, unsigned long stateIndexCount);

public:

    /**
     * Constructor
     *
     * @param callback Callback function pointer
     * @param userData Additional user-defined callback data
     */
    HallSensorStateSinkCallbackAdapter(HallSensorStateCallback callback, void* userData);

    HallSensorStateCallback* getCallbackPointerAddress(void);

}; // class HallSensorStateSinkCallbackAdapter

} // namespace dist500

} // namespace iris

#endif // DIST500_HALLSENSORSTATESINKCALLBACKADAPTER_H
