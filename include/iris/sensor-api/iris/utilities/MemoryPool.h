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

#ifndef UTILITIES_MEMORYPOOL_H
#define UTILITIES_MEMORYPOOL_H

// STL includes
#include <cstddef>

// iris includes
#include "iris/Common.h"
#include "iris/synchronization/Mutex.h"

namespace iris {

namespace utilities {

class SENSORAPI MemoryPool {

protected:

    static const unsigned long FREE_MAGIC = ('f'<<24) +('r'<<16) +('e' << 8) +'e';
    static const unsigned long USED_MAGIC = ('u'<<24) +('s'<<16) +('e' << 8) +'d';

    typedef struct _POOL_ELEMENT {
        unsigned long magic;
            void *data;
            bool initialized;
            MemoryPool* pool;
            struct _POOL_ELEMENT* next;
    } POOL_ELEMENT;

    size_t poolSize;
    size_t elementSize;
    size_t usedCount;
    unsigned char *poolMemory;
    POOL_ELEMENT* firstFree;
    POOL_ELEMENT* firstUsed;
    const char* poolName;
    iris::synchronization::Mutex mutex;
    virtual void initializeElement(void* element);
    virtual void finalizeElement(void* element);

public:

    MemoryPool(const char* poolName, size_t poolSize, size_t elementSize);
    virtual ~MemoryPool();
    void* allocElement(size_t size);
    void freeElement(void* element);
    size_t getUsedCount(void);
    size_t getFreeCount(void);

}; // class MemoryPool

} // namespace utilities

} // namespace iris
#endif // UTILITIES_MEMORYPOOL_H
