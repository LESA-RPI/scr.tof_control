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

#ifndef DIST500_COUNTRESULTSINK_H
#define DIST500_COUNTRESULTSINK_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/CountResultSource.h"

namespace iris {

namespace dist500 {

/**
 * Sink for CountResult objects
 */
class SENSORAPI CountResultSink : public Sink<CountResult*> {

public:

    /**
     * Constructor
     */
    CountResultSink();

    /**
     * Implementation of Sink's abstract processNewData method.
     * Forwards the data to processNewCountResult
     *
     * @param data Data object
     * @param index 0-based index of the picture if the total number of
     *        data objects is known, 0 otherwise
     * @param indexCount Total number of data objects (0 if unknown)
     *
     * @see Sink#processNewData
     */
    void processNewData(CountResult* data, unsigned long index, unsigned long indexCount);

    /**
     * Signals the availability of new data within the attached source.
     *
     * @param result CountResult object
     * @param countIndex 0-based index of the picture if the total number of
     *        data objects is known, 0 otherwise
     * @param countIndexCount Total number of count objects (0 if unknown)
     */
    virtual void processNewCountResult(CountResult* result,
            unsigned long countIndex, unsigned long countIndexCount) = 0;

}; // class CountResultSink

} // namespace dist500

} // namespace iris

#endif // DIST500_COUNTRESULTSINK_H
