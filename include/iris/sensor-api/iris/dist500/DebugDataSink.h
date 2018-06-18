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

#ifndef DIST500_DEBUGDATASINK_H
#define DIST500_DEBUGDATASINK_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/DebugDataSource.h"

namespace iris {

namespace dist500 {

/**
 * Sink for DebugData objects
 */
class SENSORAPI DebugDataSink: public Sink<DebugData*> {

public:

    /**
     * Constructor
     *
     * @param source Optional DoorStateSource instance to attach to
     */
    DebugDataSink(/*DebugDataSource* source = 0*/);

    /**
     * Implementation of Sink's abstract processNewData method.
     * Forwards the data to processNewDoorState
     *
     * @param data Data object
     * @param index 0-based index of the picture if the total number of
     *        data objects is known, 0 otherwise
     * @param indexCount Total number of data objects (0 if unknown)
     *
     * @see Sink#processnewData
     */
    void processNewData(DebugData* data, unsigned long index,
            unsigned long indexCount);

    /**
     * Signals the availability of new data within the attached source.
     *
     * @param data DebugData object
     * @param dataIndex 0-based index of the debug data if the total number
     *        of data objects is known, 0 otherwise
     * @param dataCount Total number of debug data objects (0 if unknown)
     */
    virtual void processNewDebugData(DebugData* data,
            unsigned long dataIndex, unsigned long dataCount) = 0;

}; // class DebugDataSink

} // namespace dist500

} // namespace iris

#endif // DIST500_DEBUGDATASINK_H
