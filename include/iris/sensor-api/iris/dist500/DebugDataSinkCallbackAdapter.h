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

#ifndef DIST500_DEBUGDATASINKCALLBACKADAPTER_H
#define DIST500_DEBUGDATASINKCALLBACKADAPTER_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/DebugDataSink.h"

namespace iris {

namespace dist500 {

/**
 * Acts as a DebugDataSink adapter class which delegates the processNewDebugData()
 * event to an external callback function.
 * This allows for integration with objects where subclassing from DebugDataSink
 * is impossible or undesired.
 */
class SENSORAPI DebugDataSinkCallbackAdapter: public DebugDataSink {
public:

    /**
     * Typedef for callback
     *
     * @param userData User-defined additional parameter for callback
     * @param data DebugData instance with data
     * @param dataIndex countIndex 0-based index of the data if the total number of
     *        data objects is known, 0 otherwise
     * @param dataCount Total number of data objects (0 if unknown)
     */
    typedef void (*DebugDataCallback)(void* userData, DebugData* data,
                                      unsigned long dataIndex, unsigned long dataCount);
protected:

    /**
     * Pointer to callback function
     */
    DebugDataCallback callback;

    /**
     * User-defined additional parameter for callback
     */
    void* userData;

    /**
     * Passes on CountResult data to the callback function
     *
     * @param data DebugData instance
     * @param dataIndex 0-based index of the picture if the total number of
     *        data objects is known, 0 otherwise
     * @param dataCount Total number of count objects (0 if unknown)
     */
    void processNewDebugData(DebugData *data, unsigned long dataIndex, unsigned long dataCount);

public:

    /**
     * Constructor
     *
     * @param source Optional DebugDataSource instance to attach to
     * @param callback Callback function pointer
     * @param userData Additional user-defined callback data
     */
    DebugDataSinkCallbackAdapter(/*DebugDataSource* source,*/ DebugDataCallback callback, void* userData);

    DebugDataCallback* getCallbackPointerAddress(void);

}; // class DebugDataSinkAdapter

} // namespace dist500

} // namespace iris

#endif // DIST500_DEBUGDATASINKCALLBACKADAPTER_H
