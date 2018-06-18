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

#ifndef SYNCHRONIZATION_MUTEX_H
#define SYNCHRONIZATION_MUTEX_H

#ifndef _MSC_VER
// boost includes
#include <boost/thread/recursive_mutex.hpp>
#endif

// iris includes
#include "iris/Common.h"

#if defined(_MSC_VER) || defined(FORCE_WIN32_MUTEX)
#include <windows.h>
#endif

namespace iris {

namespace synchronization {

// WORKAROUND !!!
// TODO find out why boost mutex does not compile on msvc2010 in case of dll build, then remove; see also Lock.h/.cpp

#if defined(_MSC_VER) || defined(FORCE_WIN32_MUTEX)

class RM {

protected:

    CRITICAL_SECTION cs;

public:

    RM();

    virtual ~RM();

    void lock(void);

    void unlock(void);

};

#endif

#if defined(_MSC_VER) || defined(FORCE_WIN32_MUTEX)
#define __MUTEX_BASE RM
#else
#define __MUTEX_BASE boost::recursive_mutex
#endif

class SENSORAPI Mutex: protected __MUTEX_BASE {

protected:

    friend class Lock;

public:

    void acquire(void);

    void release(void);

}; // class Mutex

} // namespace synchronization

} // namespace iris

#endif // SYNCHRONIZATION_MUTEX_H
