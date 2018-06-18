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

#ifndef DRIVERS_CAN_CANDRIVERIMPLEMENTATION_H
#define DRIVERS_CAN_CANDRIVERIMPLEMENTATION_H

// iris includes
#include "CanDriver.h"

namespace iris {

namespace drivers {

namespace can {

class SENSORAPI CanDriverImplementation {

protected:

    CanDriver& driver;

    CanDriverImplementation(CanDriver& driver);

    virtual void startup(const int busSpeed) = 0;

    virtual void shutdown(void) = 0;

    virtual void sendFrame(CanDriver::CanFrame& message) = 0;

    void forwardReceivedFrame(const CanDriver::CanFrame& message);

    void forwardErrorCondition(const CanDriver::CanErrorCondition& condition);

    friend class CanDriver;

}; // class CanDriverImplementation

} // namespace can

} // namespace drivers

} // namespace iris

#endif // DRIVERS_CAN_CANDRIVERIMPLEMENTATION_H
