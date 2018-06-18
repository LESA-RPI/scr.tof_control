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

#ifndef SYNCHRONIZATION_EVENT_H
#define SYNCHRONIZATION_EVENT_H

// boost includes
#include <boost/thread/condition.hpp>

// iris includes
#include "iris/Common.h"

namespace iris {

namespace synchronization {

class SENSORAPI Event {

protected:

    boost::condition_variable event;

    boost::mutex mutex;

    volatile bool signalled;

public:

    Event();

    void signal(void);

    void reset(void);

    bool waitFor(int timeoutMs);

}; // class Event

} // namespace synchronisation

} // namespace iris

#endif // SYNCHRONIZATION_EVENT_H
