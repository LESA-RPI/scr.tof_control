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

#ifndef QT_QTAGGREGATOR_H
#define QT_QTAGGREGATOR_H

// Qt includes
#include <QObject>

// iris includes
#include "../metrology/Aggregator.h"

namespace iris {

namespace qt {

/**
 * Qt adapter class for Aggregator
 */
class SENSORAPIQT QtAggregator: public QObject, public iris::metrology::Aggregator {

Q_OBJECT

public:

    /**
     * Constructor
     */
    QtAggregator();

public slots:

/**
 *
 */
void newPicture(iris::dist500::Picture* picture);

}; // class QtAggregator

} // namespace qt

} // namespace iris

#endif // QT_QTAGGREGATOR_H
