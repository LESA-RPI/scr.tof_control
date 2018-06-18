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

#ifndef DIST500_DEBUGDATA_H
#define DIST500_DEBUGDATA_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/PictureBoundData.h"

namespace iris {

namespace dist500 {

/**
 * Encapsulates debug data
 */
class SENSORAPI DebugData : public PictureBoundData {

protected:

    /**
     * Holds the size of debug data in bytes
     */
    unsigned int dataSize;

    /**
     * Holds the debug data
     */
    void* data;

    /**
     * Holds the data source ID
     */
    int dataSource;

    /**
     * Holds the debug data status
     */
    unsigned char status;

    /**
     * Controls if data pointer is free'd in destructor
     */
    bool autoFreeData;

public:

    /**
     * Constructor
     *
     * @param pictureNumber
     * @param timestamp
     * @param dataSource
     * @param status
     * @param dataSize
     * @param data
     */
    DebugData(unsigned long pictureNumber, unsigned long long timestamp, int dataSource, unsigned char status, int dataSize, void* data);

    /*DebugData(const DebugData& other);*/

    /**
     * No-arg constructor (needed for Qt signalling)
     */
    DebugData();

    /**
     * Copy constructor
     *
     * @param other Source object
     **/
    DebugData(const DebugData& other);

    /**
     * Creates a deep copy of the current instance
     **/
    DebugData* makeDeepCopy(void) const;

    /**
     * Destructor
     */
    ~DebugData();

    /**
     * Returns the data source ID
     *
     * @return Data source ID
     */
    int getDataSource(void);

    /**
     * Returns the data status
     *
     * @return Data status
     */
    unsigned char getStatus(void);

    /**
     * Returns the data size
     *
     * @return Data size in bytes
     */
    int getDataSize(void);

    /**
     * Returns the data
     *
     * @return Pointer to data
     */
    void* getData(void);

    /**
     * Enables deallocation of data pointer in destructor
     */
    void enableAutoFree(void);

}; // class DebugData

} // namespace dist500

} // namespace iris

#endif // DIST500_DEBUGDATA_H
