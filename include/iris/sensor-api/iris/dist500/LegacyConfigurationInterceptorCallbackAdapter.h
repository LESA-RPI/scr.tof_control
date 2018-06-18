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

#ifndef DIST500_LEGACYCONFIGURATIONINTERCEPTORCALLBACKADAPTER_H
#define DIST500_LEGACYCONFIGURATIONINTERCEPTORCALLBACKADAPTER_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/LegacyConfigurationInterceptor.h"

namespace iris {

namespace dist500 {

//#ifdef IRIS_INTERNAL_BUILD

/**
 * Acts as a ConfigurationInterceptor adapter class which delegates the reviewConfiguration()
 * event to an external callback function.
 * This allows for integration with objects where subclassing from ConfigurationInterceptor
 * is impossible or undesired.
 */
class SENSORAPI LegacyConfigurationInterceptorCallbackAdapter: public iris::dist500::LegacyConfigurationInterceptor {

public:

    /**
     * Typedef for callback
     *
     * @param userData User-defined additional parameter for callback
     */
    typedef void (*LegacyConfigurationInterceptorCallback)(void* userData, const unsigned char index, const unsigned char total, iris::configuration::Dist500Configuration &config);

protected:

    /**
     * Pointer to callback function
     */
    LegacyConfigurationInterceptorCallback callback;

    /**
     * User-defined additional parameter for callback
     */
    void* userData;

    /**
     * Passes on CountResult data to the callback function
     *
     * @param index 0-based sensor index within the group
     * @param total Total number of sensors within the group
     * @param config Configuration instance ready for manipulation (pre-configured regarding essential grouping and communication params)
     */
    void reviewConfiguration(const unsigned char index, const unsigned char total, iris::configuration::Dist500Configuration& config);

public:

    /**
     * Constructor
     *
     * @param callback Callback function pointer
     * @param userData Additional user-defined callback data
     */
    LegacyConfigurationInterceptorCallbackAdapter(const unsigned short functionArea,
                                                  const signed short doorNumber, const unsigned short doorDelay,
                                                  const iris::configuration::DoorGroup::DoorPolarity doorPolarity,
                                                  const signed short sensorDistance, const unsigned short mountingHeight,
                                                  const unsigned short minObjectHeight, const signed short countCurtain,
                                                  const unsigned short thresholdChildAdult,
                                                  LegacyConfigurationInterceptorCallback callback, void* userData);

}; // class LegacyConfigurationInterceptorCallbackAdapter

//#endif

} // namespace dist500

} // namespace iris

#endif // DIST500_LEGACYCONFIGURATIONINTERCEPTORCALLBACKADAPTER_H
