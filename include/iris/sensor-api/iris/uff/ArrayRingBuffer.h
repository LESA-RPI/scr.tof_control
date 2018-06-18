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

#ifndef UFF_ARRAYRINGBUFFER_H
#define UFF_ARRAYRINGBUFFER_H

// iris includes
#include "iris/Common.h"
#include "ExistingArrayRingBuffer.h"

namespace iris {

namespace uff {

template <class T> class ArrayRingBuffer: public ExistingArrayRingBuffer<T> {

protected:

    T* allocatedArray;

public:

    ArrayRingBuffer(int size, bool allowOverflow = false)
        : ExistingArrayRingBuffer<T>(allocatedArray, size, allowOverflow)
        , allocatedArray(new T[size])
    {
    }

    /*virtual ~ArrayRingBuffer() {
        delete[] allocatedArray;
    }*/

}; // template class ArrayRingBuffer

} // namespace uff

} // namespace iris

#endif // UFF_ARRAYRINGBUFFER_H
