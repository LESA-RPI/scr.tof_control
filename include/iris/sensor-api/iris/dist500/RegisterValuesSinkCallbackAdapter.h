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

#ifndef DIST500_REGISTERVALUESSINKCALLBACKADAPTER_H
#define DIST500_REGISTERVALUESSINKCALLBACKADAPTER_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/RegisterValuesSink.h"

namespace iris {

namespace dist500 {

/**
 * Acts as a RegisterValuesSink adapter class which delegates the processNewRegisterValues()
 * event to an external callback function.
 * This allows for integration with objects where subclassing from RegisterValuesSink
 * is impossible or undesired.
 */
class SENSORAPI RegisterValuesSinkCallbackAdapter: public iris::dist500::RegisterValuesSink {
public:

    /**
     * Typedef for register values callback function
     *
     * @param userData Additional user-defined callback data
     * @param values RegisterValues instance containing the new data
     * @param valueIndex 0-based index of the RegisterValue if the total number of
     *        RegisterValues is known, 0 otherwise
     * @param valueCount Total number of RegisterValues (0 if unknown)
     */
    typedef void (*RegisterValuesCallback)(void* userData, RegisterValues* values,
                                      unsigned long valueIndex, unsigned long valueCount);
protected:

    /**
     * Holds the callback function pointer
     */
    RegisterValuesCallback callback;

    /**
     * Additional user-defined callback data
     */void* userData;

    /**
     * Passes on new RegisterValues instance to the callback function
     *
     * @param values RegisterValues instance containing the new data
     * @param valueIndex 0-based index of the RegisterValue if the total number of
     *        RegisterValue is known, 0 otherwise
     * @param valueCount Total number of RegisterValues (0 if unknown)
     */
    void processNewRegisterValues(RegisterValues *values, unsigned long valueIndex, unsigned long valueCount);

public:

    /**
     * Constructor
     *
     * @param source Optional registerValuesSource instance to attach to
     * @param callback Callback function pointer
     * @param userData Additional user-defined callback data
     */
    RegisterValuesSinkCallbackAdapter(/*RegisterValuesSource* source,*/ RegisterValuesCallback callback, void* userData);

}; // class RegisterValuesCallbackAdapter

} // namespace dist500

} // namespace iris

#endif // DIST500_REGISTERVALUESSINKCALLBACKADAPTER_H
