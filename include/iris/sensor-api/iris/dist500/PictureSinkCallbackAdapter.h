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

#ifndef DIST500_PICTURESINKCALLBACKADAPTER_H
#define DIST500_PICTURESINKCALLBACKADAPTER_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/PictureSink.h"

namespace iris {

namespace dist500 {

/**
 * Acts as a PictureSink adapter class which delegates the processNewPicture()
 * event to an external callback function.
 * This allows for integration with objects where subclassing from PictureSink
 * is impossible or undesired.
 */
class SENSORAPI PictureSinkCallbackAdapter: public PictureSink {

public:

    /**
     * Typedef for picture callback function
     *
     * @param userData Additional user-defined callback data
     * @param picture Picture instance containing the new data
     * @param pictureIndex 0-based index of the picture if the total number of
     *        pictures is known, 0 otherwise
     * @param pictureIndexCount Total number of picture (0 if unknown)
     */
    typedef void (*NewPictureCallback)(void* userData, Picture* picture,
            unsigned long pictureIndex, unsigned long pictureIndexCount);

    /**
     * Constructor
     *
     * @param source Optional PictureSource instance to attach to
     * @param callback Callback function pointer
     * @param userData Additional user-defined callback data
     */
    PictureSinkCallbackAdapter(/*PictureSource *source,*/
            NewPictureCallback callback, void* userData);

protected:

    /**
     * Holds the callback function pointer
     */
    NewPictureCallback callback;

    /**
     * Additional user-defined callback data
     */
    void* userData;

    /**
     * Passes on new picture events to the callback function
     *
     * @param picture Picture instance containing the new data
     * @param pictureIndex 0-based index of the picture if the total number of
     *        pictures is known, 0 otherwise
     * @param pictureIndexCount Total number of picture (0 if unknown)
     */
    void processNewPicture(Picture* picture,
                unsigned long pictureIndex, unsigned long pictureIndexCount);

}; // class PictureSinkCallbackAdapter

} // namespace dist500

} // namespace iris

#endif // DIST500_PICTURESINKCALLBACKADAPTER_H
