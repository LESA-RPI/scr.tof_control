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

#ifndef QT_QTDIST500METATYPES_H
#define QT_QTDIST500METATYPES_H

// Qt includes
#include <QMetaType>

// iris includes
#include "iris/dist500/CountResult.h"
#include "iris/dist500/RegisterValues.h"
#include "iris/dist500/DoorState.h"

Q_DECLARE_METATYPE(iris::dist500::CountResult)
Q_DECLARE_METATYPE(iris::dist500::RegisterValues)
Q_DECLARE_METATYPE(iris::dist500::DoorState)

namespace iris {

namespace qt {

void SENSORAPIQT registerMetaTypes(void);

static struct AutoRegisterStruct {

    AutoRegisterStruct() {
        registerMetaTypes();
    }

} autoRegisterStruct;

}

}

#endif // QT_QTDIST500METATYPES_H
