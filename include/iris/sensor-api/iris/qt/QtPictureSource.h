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

#ifndef QT_QTPICTURESOURCE_H
#define QT_QTPICTURESOURCE_H

// Qt includes
#include <QObject>

// irisi includes
#include "../Common.h"

namespace iris {

namespace qt {

/**
 * Qt adapter class for PictureSource
 */
class SENSORAPIQT QtPictureSource: public QObject {

Q_OBJECT

public:

    /**
     * Constructor
     */
    QtPictureSource();

signals:

    /**
     *
     */
    void newValuesAvailable(unsigned short *values, unsigned long pictureNumber, unsigned long long timestamp);

}; // class QtPictureSource

} // namespace qt

} // namespace iris

#endif // QT_QTPICTURESOURCE_H
