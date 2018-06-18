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

#ifndef SYNCHRONIZATION_LOCK_H
#define SYNCHRONIZATION_LOCK_H

// iris includes
#include "iris/Common.h"
#include "Mutex.h"

namespace iris {

namespace synchronization {

// WORKAROUND !!!
// TODO remove when msvc2010 dll build problem is solved, see also Mutex.h/.cpp

#if defined(_MSC_VER) || defined(FORCE_WIN32_MUTEX)

class L {

protected:

    Mutex& m;

public:

    explicit L(Mutex& m);

    virtual ~L();

};

#endif

#if defined(_MSC_VER) || defined(FORCE_WIN32_MUTEX)
#define __LOCK_BASE L
#else
#define __LOCK_BASE boost::recursive_mutex::scoped_lock
#endif

class SENSORAPI Lock: public __LOCK_BASE {

public:

    explicit Lock(Mutex& mutex);

}; // class Lock

} // namespace synchronization

} // namespace iris

#endif // SYNCHRONIZATION_LOCK_H
