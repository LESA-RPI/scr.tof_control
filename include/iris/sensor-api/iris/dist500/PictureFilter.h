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

#ifndef DIST500_PICTUREFILTER_H
#define DIST500_PICTUREFILTER_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/PictureSink.h"
#include "iris/dist500/PictureSource.h"

namespace iris {

namespace dist500 {

/**
 * Interface class (ie abstract base class) defining a "picture filter".
 * A filter can simply do evaluation tasks on the picture data, but it may also
 * modify them. If modifications are done, PictureFilter automatically creates
 * copies of the original picture to avoid side effects.<br>
 * A picture filter acts itself as PictureSource, which makes it possible to
 * chain filters to others or to connect them to a sink (like an Aggregator or
 * an UffRecorder).
 *
 * @note Concrete subclasses define the actual filter behaviour by implementing
 *       the applyFilter() method.
 */
class SENSORAPI PictureFilter: public PictureSink, public PictureSource {

protected:

    /**
     * Passes on the new picture to the applyFilter() method.
     * This is the implementation of the abstract processNewPicture method
     * of PictureSink. Copies of the pictures are created automatically if
     * necessary.
     *
     * @param picture Picture instance containing the new data
     * @param pictureIndex 0-based index of the picture if the total number of
     *        pictures is known, 0 otherwise
     * @param pictureIndexCount Total number of picture (0 if unknown)
     */
    void processNewPicture(Picture* picture, unsigned long pictureIndex,
            unsigned long pictureIndexCount);

    /**
     * Performs the actual filter task.
     *
     * @param picture Picture instance containing the new data
     * @param pictureIndex Reference to 0-based index of the picture (0 if the
     *        total number of pictures is unknown)
     * @param pictureIndexCount Reference to the total number of picture (0 if
     *        unknown)
     *
     * @note Subclasses need to implement this abstract method.
     */
    virtual bool applyFilter(Picture* picture, unsigned long& pictureIndex,
            unsigned long& pictureIndexCount) = 0;

    /**
     * Flag indicating whether the filter modifies the picture data (ie whether
     * copies of the data must be made)
     */
    bool modifiesPicture;

public:

    /**
     * Constructor
     *
     * @param source Optional PictureSource instance to attach to
     * @param modifiesPicture Flag indicating whether the filter modifies the
     *        picture data (<code>true</code>) or not (<code>false</code>).
     *        If activated, every incoming picture will be copied before further
     *        processing.
     */
    PictureFilter(/*PictureSource* source,*/ bool modifiesPicture);

}; // class PictureFilter

} // namespace dist500

} // namespace iris

#endif // DIST500_PICTUREFILTER_H
