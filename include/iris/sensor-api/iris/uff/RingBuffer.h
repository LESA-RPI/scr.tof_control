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

#ifndef UFF_RINGBUFFER_H
#define UFF_RINGBUFFER_H

// iris includes
#include "iris/Common.h"
#include "iris/synchronization/Mutex.h"

namespace iris {

namespace uff {

template <class T> class RingBuffer { // TODO: create .cpp for this class

public:

    typedef T* ElementPtr;

protected:

    ElementPtr *buffer;
    int size;
    int count;
    bool allowOverflow;
    int readIndex;
    int writeIndex;
    iris::synchronization::Mutex mutex;// TODO: use lock

public:

    RingBuffer(int size, bool allowOverflow = false): size(size), allowOverflow(allowOverflow) {
        buffer = new ElementPtr[size];
        clear();
    }

    void clear(void) {
        mutex.acquire();
        count = 0;
        readIndex = 0;
        writeIndex = 0;
        mutex.release();
    }

    virtual void prepare(void) {
        for (int i = 0; i < size; ++i) {
            buffer[i] = allocElement(i);
        }
    }

    virtual ~RingBuffer() {
        delete[] buffer;
    }

    bool insert(T& element) {
        mutex.acquire();
        if (isFull()) {
            if (!allowOverflow) {
                mutex.release();
                return false;
            }
            //ElementPtr forgetPtr = buffer[writeIndex];
            //overwriteHandler(writeIndex, forgetPtr);
            count--;
        }
        ElementPtr writePtr = buffer[writeIndex];
        assignToBuffer(writeIndex, writePtr, element);
        writeIndex++;
        writeIndex %= size;
        count++;
        mutex.release();
        return true;
    }

    bool remove(T& element) {
        mutex.acquire();
        if (isEmpty()) {
            mutex.release();
            return false;
        }
        ElementPtr readPtr = buffer[readIndex];
        assignFromBuffer(readIndex, readPtr, element);
        readIndex++;
        readIndex %= size;
        count--;
        mutex.release();
        return true;
    }

    typedef void (*ELEMENT_CALLBACK) (void *userData, T& element);

    int removeAll(void* userData, ELEMENT_CALLBACK callback, int limit = 0) {
        mutex.acquire();
        int tempCount = 0;
        while (!isEmpty()) {
            T element;
            remove(element);
            callback(userData, element);
            tempCount++;
            if (limit && tempCount >= limit) {
                break;
            }
        }
        mutex.release();
        return tempCount;
    }

    int forEach(void* userData, ELEMENT_CALLBACK callback) {
        mutex.acquire();
        int tempReadIndex = readIndex;
        int tempCount = count;
        while (tempCount > 0) {
            ElementPtr readPtr = buffer[tempReadIndex];
            T element;
            assignFromBuffer(tempReadIndex, readPtr, element);
            callback(userData, element);
            tempReadIndex++;
            tempReadIndex %= size;
            tempCount--;
        }
        tempCount = count;
        mutex.release();
        return count;
    }

    int getSize(void) {
        return size;
    }

    bool isOVerflowAllowed(void) {
        return allowOverflow;
    }

    int getElementCount(void) {
        return count;
    }

    bool isEmpty(void) {
        mutex.acquire();
        bool empty = count == 0;
        mutex.release();
        return empty;
    }

    bool isFull(void) {
        mutex.acquire();
        bool full = count == size;
        mutex.release();
        return full;
    }

    int getFreeCount(void) {
        mutex.acquire();
        int free = size - count;
        mutex.release();
        return free;
    }

protected:

    virtual void assignToBuffer(int index, ElementPtr dst, T& src) {
        IRIS_UNUSED(index)
        *dst = src;
    }

    virtual void assignFromBuffer(int index, ElementPtr src, T& dst) {
        IRIS_UNUSED(index)
        dst = *src;
    }

    virtual ElementPtr allocElement(int index) {
        IRIS_UNUSED(index)
        return new T;
    }

    virtual void freeElement(int index, ElementPtr element) {
        IRIS_UNUSED(index)
        delete element;
    }

}; // template class RingBuffer

} // namespace uff

} // namespace iris

#endif // UFF_RINGBUFFER_H
