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

#ifndef QT_QTUFFPLAYER_H
#define QT_QTUFFPLAYER_H

// Qt includes
#include <QObject>

// iris includes
#include "../uff/UffPlayer.h"
#include "../dist500/PictureSink.h"
#include "../dist500/RegisterValuesSink.h"
#include "../dist500/DoorStateSink.h"
#include "QtDist500MetaTypes.h"

namespace iris {

namespace qt {

/**
 * Qt adapter class for UffPlayer
 */
class SENSORAPIQT QtUffPlayer: public QObject,
        public iris::uff::UffPlayer,
        protected iris::dist500::PictureSink,
        protected iris::dist500::RegisterValuesSink,
        protected iris::dist500::DoorStateSink {

Q_OBJECT

protected:

    /**
     *
     */
    void processNewPicture(iris::dist500::Picture* picture,
            unsigned long pictureIndex, unsigned long pictureIndexCount);

    void processNewRegisterValues(iris::dist500::RegisterValues *values, unsigned long valueIndex, unsigned long valueCount);

    void processNewDoorState(iris::dist500::DoorState *state, unsigned long stateIndex, unsigned long stateCount);

signals:

/**
 *
 */
void newPicture(iris::dist500::Picture* picture, unsigned long pictureIndex, unsigned long pictureIndexCount);

void newRegisterValues(iris::dist500::RegisterValues values, unsigned long pictureIndex, unsigned long pictureIndexCount);

void newDoorState(iris::dist500::DoorState state, unsigned long pictureIndex, unsigned long pictureIndexCount);

public:

    /**
     * Constructor
     *
     * @param parent Parent QObject
     */
    explicit QtUffPlayer(QObject *parent);

    /**
     * Destructor
     */
    ~QtUffPlayer();

    bool open(const QString& filename);

}; // class QtUffPlayer

} // namespace qt

} // namespace iris

#endif // QT_QTUFFPLAYER_H
