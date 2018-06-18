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

#ifndef DIST500_DOORSTATESINKCALLBACKADAPTER_H
#define DIST500_DOORSTATESINKCALLBACKADAPTER_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/DoorStateSink.h"

namespace iris {

namespace dist500 {

/**
 * Acts as a DoorStateSink adapter class which delegates the processNewDoorState()
 * event to an external callback function.
 * This allows for integration with objects where subclassing from DoorStateSink
 * is impossible or undesired.
 */
class SENSORAPI DoorStateSinkCallbackAdapter: public DoorStateSink {

public:

    /**
     * Typedef for callback
     *
     * @param userData User-defined additional parameter for callback
     * @param doorState DoorState instance with data
     * @param stateIndex countIndex 0-based index of the picture if the total number of
     *        state objects is known, 0 otherwise
     * @param stateIndexCount Total number of state objects (0 if unknown)
     */
    typedef void (*DoorStateCallback)(void* userData, DoorState* doorState,
                                      unsigned long stateIndex, unsigned long stateIndexCount);

protected:

    /**
     * Pointer to callback function
     */
    DoorStateCallback callback;

    /**
     * User-defined additional parameter for callback
     */
    void* userData;

    /**
     * Passes on DoorState data to the callback function
     *
     * @param state DoorState instance
     * @param stateIndex 0-based index of the picture if the total number of
     *        data objects is known, 0 otherwise
     * @param stateIndexCount Total number of state objects (0 if unknown)
     */
    void processNewDoorState(DoorState* state,
                unsigned long stateIndex, unsigned long stateIndexCount);

public:

    /**
     * Constructor
     *
     * @param source Optional DoorStateSource instance to attach to
     * @param callback Callback function pointer
     * @param userData Additional user-defined callback data
     */
    DoorStateSinkCallbackAdapter(/*DoorStateSource* source,*/ DoorStateCallback callback, void* userData);

    DoorStateCallback* getCallbackPointerAddress(void);

}; // class DoorStateSinkCallbackAdapter

} // namespace dist500

} // namespace iris

#endif // DIST500_DOORSTATESINKCALLBACKADAPTER_H
