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

#ifndef UFF_EXISTINGARRAYRINGBUFFER_H
#define UFF_EXISTINGARRAYRINGBUFFER_H

// iris includes
#include "iris/Common.h"
#include "RingBuffer.h"

namespace iris {

namespace uff {

template <class T> class ExistingArrayRingBuffer: public RingBuffer<T> {

protected:

    T* array;

    typename RingBuffer<T>::ElementPtr allocElement(int index) {
        return array + index;
    }

    void freeElement(int index, typename RingBuffer<T>::ElementPtr element) {
        IRIS_UNUSED(index)
        IRIS_UNUSED(element)
    }

public:

    ExistingArrayRingBuffer(T* array, int size, bool allowOverflow = false): RingBuffer<T>(size, allowOverflow), array(array) {
    }

}; // template class ExistingArrayRingBuffer

} // namespace uff

} // namespace iris

#endif // UFF_EXISTINGARRAYRINGBUFFER_H
