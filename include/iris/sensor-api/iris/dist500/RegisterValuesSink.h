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

#ifndef DIST500_REGISTERVALUESSINK_H
#define DIST500_REGISTERVALUESSINK_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/RegisterValuesSource.h"

namespace iris {

namespace dist500 {

/**
 * Sink for RegisterValues objects
 */
class SENSORAPI RegisterValuesSink: public Sink<RegisterValues*> {

public:

    /**
     * Constructor
     *
     * @param source Optional PictureSource instance to attach to
     */
    RegisterValuesSink(/*RegisterValuesSource* source = 0*/);

    /**
     * Implementation of Sink's abstract processNewData method.
     * Forwards the data to processNewCountResult
     *
     * @param data Data object
     * @param index 0-based index of the picture if the total number of
     *        data objects is known, 0 otherwise
     * @param indexCount Total number of data objects (0 if unknown)
     *
     * @see Sink#processnewData
     */
    void processNewData(RegisterValues* data, unsigned long index,
            unsigned long indexCount);

    /**
     * Signals the availability of new data within the attached source.
     * This callback method is abstract. Derived RegisterValuesSink classed therefore
     * need to implement it.
     *
     * @param values RegisterValues instance containing the new data
     * @param valueIndex 0-based index of the RegisterValue if the total number of
     *        RegisterValue is known, 0 otherwise
     * @param valueCount Total number of RegisterValues (0 if unknown)
     */
    virtual void processNewRegisterValues(RegisterValues* values,
            unsigned long valueIndex, unsigned long valueCount) = 0;

}; // class RegisterValuesSink

} // namespace dist500

} // namespace iris

#endif // DIST500_REGISTERVALUESSINK_H
