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

#ifndef QT_QTUFFRECORDER_H
#define QT_QTUFFRECORDER_H

// Qt includes
#include <QObject>

// iris includes
#include "../uff/UffRecorder.h"
#include "QtDist500MetaTypes.h"

namespace iris {

namespace qt {

/**
 * Qt adapter class for UffRecorder
 */
class SENSORAPIQT QtUffRecorder: public QObject, public iris::uff::UffRecorder {

Q_OBJECT

public:

    /**
     * Constructor
     *
     * @param parent Parent QObject
     */
    explicit QtUffRecorder(QObject *parent, const std::string& fileName, const std::string appName, const std::string appVersion,
                           const std::string userName, const std::string location,
                           iris::dist500::SensorInfoProvider* sensorInfoProvider);

    /**
     * Destructor
     */
    ~QtUffRecorder();

public slots:

    void saveValues(iris::dist500::Picture*,ulong index,ulong indexCount);
    void saveCountResult(iris::dist500::CountResult,ulong,ulong);
    void saveRegisterValues(iris::dist500::RegisterValues,ulong,ulong);
    void saveDoorState(iris::dist500::DoorState,ulong,ulong);

}; // class QtUffRecorder

} // namespace qt

} // namespace iris

#endif // QT_QTUFFRECORDER_H
