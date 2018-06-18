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

#ifndef UTILITIES_MAILBOX_H
#define UTILITIES_MAILBOX_H

// iris includes
#include "iris/Common.h"
#include "iris/synchronization/Mutex.h"
#include "iris/synchronization/Semaphore.h"

namespace iris {

namespace utilities {

class SENSORAPI MailBox {

protected:
    int capacity;
    int fillLevel;
    int readIndex;
    int writeIndex;
    void** entries;
    iris::synchronization::Mutex* mutex;
    iris::synchronization::Semaphore* getSema;
    iris::synchronization::Semaphore* putSema;
public:
    MailBox(int capacity);
    virtual ~MailBox();
    bool put(void* entry, int timeoutMs);
    bool get(void* &entry, int timeousMs);
    int getCapacity(void) const;
    int getFillLevel(void) const;
    void clear(void);

}; // class MailBox

} // namespace utilities

} // namespace iris

#endif // UTILITIES_MAILBOX_H
