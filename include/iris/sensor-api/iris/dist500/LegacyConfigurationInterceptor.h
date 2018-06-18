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

#ifndef DIST500_LEGACYCONFIGURATIONINTERCEPTOR_H
#define DIST500_LEGACYCONFIGURATIONINTERCEPTOR_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/FirmwareController.h"
#include "iris/configuration/Configuration.h"
#include "iris/dist500/Dist500.h"

namespace iris {

namespace dist500 {

class SENSORAPI LegacyConfigurationInterceptor: public iris::dist500::FirmwareController::ConfigurationInterceptor {
protected:
    const unsigned short functionArea;
    const signed short doorNumber;
    const unsigned short doorDelay;
    const iris::configuration::DoorGroup::DoorPolarity doorPolarity;
    const signed short sensorDistance;
    const unsigned short mountingHeight;
    const unsigned short minObjectHeight;
    const unsigned short thresholdChildAdult;
    const signed short countCurtain;

public:
    LegacyConfigurationInterceptor(const unsigned short functionArea,
            const signed short doorNumber, const unsigned short doorDelay,
            const iris::configuration::DoorGroup::DoorPolarity doorPolarity,
            const signed short sensorDistance, const unsigned short mountingHeight,
            const unsigned short minObjectHeight, const signed short countCurtain,
            const unsigned short thresholdChildAdult);
    void reviewConfiguration(const unsigned char index, const unsigned char total, iris::configuration::Dist500Configuration& config);
};

} // namespace dist500

} // namespace iris

#endif // DIST500_LEGACYCONFIGURATIONINTERCEPTOR_H
