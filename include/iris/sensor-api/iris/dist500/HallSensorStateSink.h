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

#ifndef DIST500_HALLSENSORSTATESINK_H
#define DIST500_HALLSENSORSTATESINK_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/HallSensorStateSource.h"

namespace iris {

namespace dist500 {

/**
 * Sink for HallSensorState objects
 */
class SENSORAPI HallSensorStateSink: public Sink<HallSensorState*> {

public:

    /**
     * Constructor
     *
     */
    HallSensorStateSink();

    /**
     * Implementation of Sink's abstract processNewData method.
     * Forwards the data to processNewHallSensorState
     *
     * @param data Data object
     * @param index 0-based index of the picture if the total number of
     *        data objects is known, 0 otherwise
     * @param indexCount Total number of data objects (0 if unknown)
     *
     * @see Sink#processnewData
     */
    void processNewData(HallSensorState* data, unsigned long index, unsigned long indexCount);

    /**
     * Signals the availability of new data within the attached source.
     *
     * @param state HallSensorState object
     * @param stateIndex 0-based index of the state if the total number
     *        of data objects is known, 0 otherwise
     * @param stateCount Total number of state  objects (0 if unknown)
     */
    virtual void processNewHallSensorState(HallSensorState* state, unsigned long stateIndex, unsigned long stateCount) = 0;

}; // class HallSensorStateSink

} // namespace dist500

} // namespace iris

#endif // DIST500_HALLSENSORSTATESINK_H
