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

#ifndef DIST500_DOORSTATESOURCE_H
#define DIST500_DOORSTATESOURCE_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/DoorState.h"
#include "iris/dist500/Source.h"

namespace iris {

namespace dist500 {

/**
 * Source for DoorState objects
 */
class SENSORAPI DoorStateSource: public Source<DoorState*> {

public:

    /**
     * Propagates a new DoorState to all attached sinks
     *
     * @param data DoorState to be propagated
     * @param index 0-based index of the data if the total number of
     *        DoorState objects is known, 0 otherwise
     * @param indexCount Total number of DoorState objects (0 if unknown)
     */
    void pushDoorStateToSinks(DoorState *data, unsigned long index,
                              unsigned long indexCount);

}; // class DoorStateSource

} // namespace dist500

} // namespace iris

#endif // DIST500_DOORSTATESOURCE_H
