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

#ifndef DIST500_WORKINGMODESTATUSSOURCE_H
#define DIST500_WORKINGMODESTATUSSOURCE_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/WorkingModeStatus.h"
#include "iris/dist500/Source.h"

namespace iris {

namespace dist500 {

/**
 * Source for WorkingModeStatus objects
 */
class SENSORAPI WorkingModeStatusSource: public Source<WorkingModeStatus*> {

public:

    /**
     * Propagates a new WorkingModeStatus to all attached sinks
     *
     * @param data WorkingModeStatus to be propagated
     * @param index 0-based index of the data if the total number of
     *        WorkingModeStatus objects is known, 0 otherwise
     * @param indexCount Total number of WorkingModeStatus objects (0 if unknown)
     */
    void pushWorkingModeStatusToSinks(WorkingModeStatus *data, unsigned long index,
                              unsigned long indexCount);

}; // class WorkingModeStatusSource

} // namespace dist500

} // namespace iris

#endif // DIST500_WORKINGMODESTATUSSOURCE_H
