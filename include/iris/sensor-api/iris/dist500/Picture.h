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

#ifndef DIST500_PICTURE_H
#define DIST500_PICTURE_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/PictureBoundData.h"

namespace iris {

namespace dist500 {

enum {
    SaturationFlag = 0x4
};

#pragma pack(1)

/**
 * Typedef for a decoded (into flags and value) pixel
 */
typedef struct {

    /**
     * Values (eg distance or amplitude) in lower 12 bits
     */
    unsigned short value : 12,

    /**
     * Flags (eg saturation) in upper nibble
     */
    flags : 4;
    
} FlagsAndValue;

/**
 * Typedef for a pixel, either as "raw" 16 bit number or in decoded (flags plus
 * value) form
 */
typedef union {

    /**
     * Raw value (full 16 bit value)
     */
    unsigned short raw;

    /**
     * Decoded value
     */
    FlagsAndValue decoded;

} Pixel;

#pragma pack()

/**
 * Typedef for a DIST500 subpicture (eg distance or amplitude)
 */
typedef union {

    /**
     * Pixels in a one-dimensional array
     */
    Pixel linear[500];

    /**
     * Pixels in a two-dimensional array
     */
    Pixel matrix[20][25];

} Pixels500;

/**
 * Typedef for a full DIST500 picture (distance plus amplitude), treated as one
 * big picture
 */
typedef union {

    /**
     * Pixels in a one-dimensional array
     */
    Pixel linear[1000];

    /**
     * Pixels in a two-dimensional array
     */
    Pixel matrix[40][25];

} Pixels1000;

/**
 * Typedef for a full DIST500 picture (distance plus amplitude), adressable as
 * two subpictures
 */
typedef struct {

    /**
     * Distance values
     */
    Pixels500 distances;

    /**
     * Amplitude values
     */
    Pixels500 amplitudes;

} SubPics;

/**
 * Typedef for a full DIST500 picture, addressable in an arbitrary way
 */
typedef union {

    /**
     * Two separate pictures
     */
    SubPics subPictures;

    /**
     * One virtual big picture
     */
    Pixels1000 wholePicture;

} Pic;

/**
 * This class represents a full DIST500 picture along with some metadata (eg
 * picture number and timestamp)
 */
class SENSORAPI Picture: public PictureBoundData {

protected:

    /**
     * Flag indicating whether the Pic pointer points to an existing value array
     * (<code>false</code>) or to a copy made by the constructor at another
     * memory location (<code>true</code>)
     *
     * @see picture
     */
    bool copy;

    /**
     * Holds the pixel values
     *
     * @see copy
     */
    Pic* picture;

public:

    /**
     * Constructor
     *
     * @param pictureNumber Picture number
     * @param timestamp Timestamp
     * @param picture Pixel data as Pic pointer
     * @param makeCopy Pixel data copy flag (<code>true</code> make copy,
     *        <code>false</code> don't)
     */
    Picture(unsigned long pictureNumber, unsigned long long timestamp,
            Pic* picture, bool makeCopy = false);

    /**
     * Constructor
     *
     * @param pictureNumber Picture number
     * @param timestamp Timestamp
     * @param values Pixel data as short int pointer
     * @param makeCopy Pixel data copy flag (<code>true</code> make copy,
     *        <code>false</code> don't)
     */
    Picture(unsigned long pictureNumber, unsigned long long timestamp,
            unsigned short* values, bool makeCopy = false);

    /**
     * Copy constructor
     *
     * @param source Picture instance to be cloned
     */
    Picture(const Picture& source);

    /**
     * No-arg constructor (needed for Qt)
     */
    Picture();

    /**
     * Destructor
     */
    virtual ~Picture();

    /**
     * Returns the pixel data pointer as Pic instance
     *
     * @see copy
     * @see picture
     */
    Pic* getPicture(void);

    /**
     * Returns the copy flag
     *
     * @return <code>true</code> if pic is a copy, <code>false</code> otherwise
     */
    bool isCopy(void);

    /**
     * Assignment operator
     *
     * @param other Source Picture instance
     */
    Picture& operator =(Picture& other);

}; // class Picture

} // namespace dist500

} // namespace iris

#endif // DIST500_PICTURE_H
