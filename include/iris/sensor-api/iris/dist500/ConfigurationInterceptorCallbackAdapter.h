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

#ifndef DIST500_CONFIGURATIONINTERCEPTORCALLBACKADAPTER_H
#define DIST500_CONFIGURATIONINTERCEPTORCALLBACKADAPTER_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/FirmwareController.h"

namespace iris {

namespace dist500 {

/**
 * Acts as a ConfigurationInterceptor adapter class which delegates the reviewConfiguration()
 * event to an external callback function.
 * This allows for integration with objects where subclassing from ConfigurationInterceptor
 * is impossible or undesired.
 */
class SENSORAPI ConfigurationInterceptorCallbackAdapter: public iris::dist500::FirmwareController::ConfigurationInterceptor {

public:

    /**
     * Typedef for callback
     *
     * @param userData User-defined additional parameter for callback
     */
    typedef void (*ConfigurationInterceptorCallback)(void* userData, const unsigned char index, const unsigned char total, iris::configuration::Dist500Configuration &config);

protected:

    /**
     * Pointer to callback function
     */
    ConfigurationInterceptorCallback callback;

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
    ConfigurationInterceptorCallbackAdapter(ConfigurationInterceptorCallback callback, void* userData);

}; // class ConfigurationInterceptorCallbackAdapter

} // namespace dist500

} // namespace iris

#endif // DIST500_CONFIGURATIONINTERCEPTORCALLBACKADAPTER_H
