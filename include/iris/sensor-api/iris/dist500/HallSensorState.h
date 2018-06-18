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

#ifndef DIST500_HALLSENSORSTATE_H
#define DIST500_HALLSENSORSTATE_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/PictureBoundData.h"

namespace iris {

namespace dist500 {

/**
 * Encapsulates a door state
 */
class SENSORAPI HallSensorState : public PictureBoundData {

protected:

    /**
     * Holds the hall sensor state
     */
    unsigned char state;

public:

    /**
     * Constructor
     *
     * @param pictureNumber
     * @param timestamp
     * @param state
     */
    HallSensorState(unsigned long pictureNumber, unsigned long long timestamp, unsigned char state);

    /**
     * No-arg constructor (needed for Qt signalling)
     */
    HallSensorState();

    /**
     * Returns the hall sensor state
     *
     * @return Hall sensor state
     */
    unsigned char getState(void) const;

    void setState(unsigned char state);

}; // class HallSensorState

} // namespace dist500

} // namespace iris

#endif // DIST500_HALLSENSORSTATE_H
