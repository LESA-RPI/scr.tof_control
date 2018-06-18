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

#ifndef DIST500_COUNTRESULTSOURCE_H
#define DIST500_COUNTRESULTSOURCE_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/CountResult.h"
#include "iris/dist500/Source.h"

namespace iris {

namespace dist500 {

/**
 * Source for CountResult objects
 */
class SENSORAPI CountResultSource: public Source<CountResult*> {

public:

    /**
     * Propagates a new CountResult to all attached sinks
     *
     * @param result CountResult to be propagated
     * @param index 0-based index of the data if the total number of
     *        CountResult objects is known, 0 otherwise
     * @param indexCount Total number of CountResult objects (0 if unknown)
     */
    void pushCountResultToSinks(CountResult* result, unsigned long index,
                                unsigned long indexCount);

}; // class CountResultSource

} // namespace dist500

} // namespace iris

#endif // DIST500_COUNTRESULTSOURCE_H
