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

#ifndef DIST500_PICTURESINK_H
#define DIST500_PICTURESINK_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/PictureSource.h"

namespace iris {

namespace dist500 {

/**
 * Sink for Picture objects
 **/
class SENSORAPI PictureSink: public Sink<Picture*> {

public:

    /**
     * Constructor
     *
     * @param source Optional PictureSource instance to attach to
     */
    PictureSink(/*PictureSource* source = 0*/);

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
    void processNewData(Picture* data, unsigned long index,
            unsigned long indexCount);

    /**
     * Signals the availability of new data within the attached source.
     * This callback method is abstract. Derived PictureSink classed therefore
     * need to implement it.
     *
     * @param picture Picture instance containing the new data
     * @param pictureIndex 0-based index of the picture if the total number of
     *        pictures is known, 0 otherwise
     * @param pictureIndexCount Total number of picture (0 if unknown)
     */
    virtual void processNewPicture(Picture* picture,
            unsigned long pictureIndex, unsigned long pictureIndexCount) = 0;

}; // class PictureSink

} // namespace dist500

} // namespace uff

#endif // DIST500_PICTURESINK_H
