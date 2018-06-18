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

#ifndef DIST500_WORKINGMODESTATUS_H
#define DIST500_WORKINGMODESTATUS_H

// iris includes
#include "iris/Common.h"
#include "iris/configuration/Configuration.h"
#include "iris/dist500/PictureBoundData.h"

namespace iris {

namespace dist500 {

/**
 * Encapsulates a working mode. @see Dist500Base::getWorkingMode
 */
class SENSORAPI WorkingModeStatus : public PictureBoundData {

protected:

    /**
     * Holds the working mode status
     */
    iris::uip::working_mode mode;

public:

    /**
     * Constructor
     *
     * @param pictureNumber
     * @param timestamp
     * @param mode
     */
    WorkingModeStatus(unsigned long pictureNumber, unsigned long long timestamp, iris::uip::working_mode mode);

    /*WorkingModeStatus(const WorkingModeStatus& other);*/

    /**
     * No-arg constructor (needed for Qt signalling)
     */
    WorkingModeStatus();

    /**
     * Returns the working mode
     *
     * @return Working mode
     */
    iris::uip::working_mode getMode(void);

    void setMode(iris::uip::working_mode mode);

}; // class WorkingModeStatus

} // namespace dist500

} // namespace iris

#endif // DIST500_WORKINGMODESTATUS_H
