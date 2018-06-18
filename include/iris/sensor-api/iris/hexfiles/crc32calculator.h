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

#ifndef HEXFILES_CRC32CALCULATOR_H
#define HEXFILES_CRC32CALCULATOR_H

// iris includes
#include "iris/Common.h"

namespace iris {

namespace hexfiles {

/**
 * Provides CRC32 calculation
 */
class SENSORAPI Crc32Calculator {

protected:

    /**
     * Holds the precomputed CRC lookup table
     */
    static const unsigned int crc32table[256];

public:

    /**
     * Computes the CRC32 value of the given word array. Note: may be problematic with uneven sizes.
     *
     * @param start Start address
     * @param wordSize Length of data block in words
     */
    static unsigned int computeCRC(const unsigned short *start, unsigned int wordSize);
            
    /**
     * Computes the CRC32 value of the given byte array.
     *
     * @param start Start address
     * @param byteSize Length of data block in bytes
     */
     static unsigned int computeCrcByByte(const unsigned char *start, unsigned int byteSize);

}; // class Crc32Calculator

} // namespace hexfiles

} // namespace iris

#endif // HEXFILES_CRC32CALCULATOR_H
