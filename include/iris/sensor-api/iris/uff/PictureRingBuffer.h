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

#ifndef UFF_PICTURERINGBUFFER_H
#define UFF_PICTURERINGBUFFER_H

// iris includes
#include "iris/Common.h"
#include "ArrayRingBuffer.h"
#include "iris/dist500/PictureSink.h"
#include "iris/dist500/RegisterValuesSink.h"

namespace iris {

namespace uff {

typedef struct {
    iris::dist500::Picture p;
    //iris::dist500::RegisterValues r;
} PictureAndRegisterValues;

class SENSORAPI PictureRingBuffer: public ArrayRingBuffer<PictureAndRegisterValues>, public iris::dist500::PictureSource, public iris::dist500::PictureSink,
    public iris::dist500::RegisterValuesSource, public iris::dist500::RegisterValuesSink {

protected:

    static void flushCallback(void* userData, PictureAndRegisterValues& picture);

public:

    PictureRingBuffer(int size, bool allowOverflow = true);

    void processNewPicture(iris::dist500::Picture* picture,
                unsigned long pictureIndex, unsigned long pictureIndexCount);

    void processNewRegisterValues(iris::dist500::RegisterValues *values, unsigned long valueIndex,
                                    unsigned long valueCount);

    int flushToSink(int limit);

};

} // namespace uff

} // namespace iris

#endif // UFF_PICTURERINGBUFFER_H
