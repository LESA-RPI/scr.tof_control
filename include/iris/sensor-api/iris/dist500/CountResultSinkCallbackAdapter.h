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

#ifndef DIST500_COUNTRESULTSINKCALLBACKADAPTER_H
#define DIST500_COUNTRESULTSINKCALLBACKADAPTER_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/CountResultSink.h"

namespace iris {

namespace dist500 {

/**
 * Acts as a CountResultSink adapter class which delegates the processNewCountResult()
 * event to an external callback function.
 * This allows for integration with objects where subclassing from CountResultSink
 * is impossible or undesired.
 */
class SENSORAPI CountResultSinkCallbackAdapter: public CountResultSink {
public:

    /**
     * Typedef for callback
     *
     * @param userData User-defined additional parameter for callback
     * @param countResult CountResult instance with data
     * @param countIndex countIndex 0-based index of the picture if the total number of
     *        data objects is known, 0 otherwise
     * @param countCount Total number of count objects (0 if unknown)
     */
    typedef void (*CountResultCallback)(void* userData, CountResult* countResult,
                                      unsigned long countIndex, unsigned long countCount);
protected:

    /**
     * Pointer to callback function
     */
    CountResultCallback callback;

    /**
     * User-defined additional parameter for callback
     */
    void* userData;

    /**
     * Passes on CountResult data to the callback function
     *
     * @param result CountResult instance
     * @param countIndex 0-based index of the picture if the total number of
     *        data objects is known, 0 otherwise
     * @param countCount Total number of count objects (0 if unknown)
     */
    void processNewCountResult(CountResult* result, unsigned long countIndex, unsigned long countCount);

public:

    /**
     * Constructor
     *
     * @param source Optional CountResultSource instance to attach to
     * @param callback Callback function pointer
     * @param userData Additional user-defined callback data
     */
    CountResultSinkCallbackAdapter(/*CountResultSource* source,*/ CountResultCallback callback, void* userData);

}; // class CountResultSinkAdapter

} // namespace dist500

} // namespace iris

#endif // DIST500_COUNTRESULTSINKCALLBACKADAPTER_H
