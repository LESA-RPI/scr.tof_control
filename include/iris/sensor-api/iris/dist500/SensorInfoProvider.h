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

#ifndef DIST500_SENSORINFOPROVIDER_H
#define DIST500_SENSORINFOPROVIDER_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/SensorInfo.h"

namespace iris {

namespace dist500 {

/**
 * Abstract class defining an interface for classes that can provide sensor
 * metadata (such as physical sensors or UFF files)
 */
class SENSORAPI SensorInfoProvider {

public:

    /**
     * Retrieves information about the sensor
     *
     * @param forceRefresh
     *
     * @return SensorInfo instance with relevant data
     */
    virtual SensorInfo getSensorInfo(bool forceRefresh = false) = 0;

    /**
     * Clears the sensor information cache
     */
    virtual void invalidateSensorInfo(void) = 0;

    /**
     * Checks whether a (potentially) cached sensor info is available
     *
     * @return <code>true</code> if available, <code>false</code>
     *         otherwise
     */
    virtual bool hasSensorInfo(void) const = 0;

}; // class SensorInfoProvider

} // namespace dist500

} // namespace iris

#endif // DIST500_SENSORINFOPROVIDER_H
