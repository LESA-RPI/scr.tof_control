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

#ifndef DIST500_WORKINGMODESTATUSSINKCALLBACKADAPTER_H
#define DIST500_WORKINGMODESTATUSSINKCALLBACKADAPTER_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/WorkingModeStatusSink.h"

namespace iris {

namespace dist500 {

/**
 * Acts as a WorkingModeStatusSink adapter class which delegates the processNewWorkingModeStatus()
 * event to an external callback function.
 * This allows for integration with objects where subclassing from WorkingModeStatusSink
 * is impossible or undesired.
 */
class SENSORAPI WorkingModeStatusSinkCallbackAdapter: public WorkingModeStatusSink {

public:

    /**
     * Typedef for callback
     *
     * @param userData User-defined additional parameter for callback
     * @param workingModeStatus WorkingModeStatus instance with data
     * @param statusIndex countIndex 0-based index of the picture if the total number of
     *        status objects is known, 0 otherwise
     * @param statusIndexCount Total number of state objects (0 if unknown)
     */
    typedef void (*WorkingModeStatusCallback)(void* userData, WorkingModeStatus* workingModeStatus,
                                      unsigned long statusIndex, unsigned long statusIndexCount);

protected:

    /**
     * Pointer to callback function
     */
    WorkingModeStatusCallback callback;

    /**
     * User-defined additional parameter for callback
     */
    void* userData;

    /**
     * Passes on WorkingModeStatus data to the callback function
     *
     * @param status WorkingModeStatus instance
     * @param statusIndex 0-based index of the picture if the total number of
     *        data objects is known, 0 otherwise
     * @param statusIndexCount Total number of state objects (0 if unknown)
     */
    void processNewWorkingModeStatus(WorkingModeStatus* status,
                unsigned long statusIndex, unsigned long statusIndexCount);

public:

    /**
     * Constructor
     *
     * @param source Optional HallSensorStateSource instance to attach to
     * @param callback Callback function pointer
     * @param userData Additional user-defined callback data
     */
    WorkingModeStatusSinkCallbackAdapter(/*WorkingModeStatusSource* source,*/ WorkingModeStatusCallback callback, void* userData);

    WorkingModeStatusCallback* getCallbackPointerAddress(void);

}; // class WorkingModeStatusSinkCallbackAdapter

} // namespace dist500

} // namespace iris

#endif // DIST500_WORKINGMODESTATUSSINKCALLBACKADAPTER_H
