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

#ifndef THREADS_THREAD_H
#define THREADS_THREAD_H

#if defined(UNDER_CE) && !defined(OWN_WIN_THREAD_IMPL)
#define OWN_WIN_THREAD_IMPL
#endif

// boost includes
#ifndef OWN_WIN_THREAD_IMPL
#include <boost/thread/thread.hpp>
#endif

// iris includes
#include "iris/Common.h"

// OS dependent includes
#ifdef OWN_WIN_THREAD_IMPL
    #include <windows.h>
#endif

namespace iris {

namespace threads {

#ifndef OWN_WIN_THREAD_IMPL
class SENSORAPI Thread {

protected:

    void *userData;

    boost::thread *thread;

    class ThreadWrapper {

    protected:

        Thread* th;

    public:

        ThreadWrapper(Thread* th);

        void operator()();

    };

    volatile bool terminationRequested;

public:

    Thread(void* userData = 0, char* name = 0);
    
    virtual ~Thread();

    virtual unsigned int execute(void) = 0;

    bool waitFor(int timeoutMs);

    void terminate(void);

    bool isTerminated(void);

    static void sleep(int millis);

    void start(void);
    
protected:

    ThreadWrapper* wrapperInstance;

}; // class Thread
#else
class SENSORAPI Thread {

protected:

    void *userData;

    volatile bool terminationRequested;

    static unsigned int WINAPI _execute(void* self);

    HANDLE handle;

public:

    Thread(void* userData = 0, char* name = 0);

    virtual unsigned int execute(void) = 0;

    bool waitFor(int timeoutMs);

    void terminate(void);

    bool isTerminated(void);

    static void sleep(int millis);

    void start(void);

}; // class Thread
#endif

} // namespace synchronization

} // namespace iris

#ifdef SENSORAPI_DLL
    #ifdef BOOST_SYSTEM_NO_DEPRECATED
        #undef BOOST_SYSTEM_NO_DEPRECATED
        #if (BOOST_VERSION >=  105700)
            #include <boost/system/detail/error_code.ipp>
        #else
            #error Requires Boost 1.57 or higher
        #endif
        #define BOOST_SYSTEM_NO_DEPRECATED
    #endif
#endif


#endif // THREADS_THREAD_H
