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

#ifndef METROLOGY_AGGREGATORV2_H
#define METROLOGY_AGGREGATORV2_H

// STL includes
#include <list>
#include <vector>

// iris includes
#include "iris/Common.h"
#include "iris/dist500/PictureSink.h"

namespace iris {

namespace metrology {

/**
 * Class capable of computing basic statistical figures based on a number of
 * pictures (results are per pixel).
 * Saturated pixels are recognized and handled separately
 */
class SENSORAPI AggregatorV2: public iris::dist500::PictureSink {

    enum {
        COL_COUNT = 25
    };

    enum {
        SINGLE_PIC_ROW_COUNT = 20
    };

    enum {
        DOUBLE_PIC_ROW_COUNT = 2 * SINGLE_PIC_ROW_COUNT
    };

    /**
     * Total number of values per sub-picture (20 * 25 = 500)
    */
    enum {
        SINGLE_PIC_PIXEL_COUNT = SINGLE_PIC_ROW_COUNT * COL_COUNT
    };

    /**
     * Total number of values per sub-picture pair (40 * 25 = 1000)
    */
    enum {
        DOUBLE_PIC_PIXEL_COUNT = DOUBLE_PIC_ROW_COUNT * COL_COUNT
    };

    template <class T> class Dist500ValueMatrix {

    public:

        typedef union {

            T linear[SINGLE_PIC_PIXEL_COUNT];

            T matrix[SINGLE_PIC_ROW_COUNT][COL_COUNT];

        } Pixels500;

        typedef union {

            T linear[DOUBLE_PIC_PIXEL_COUNT];

            T matrix[DOUBLE_PIC_ROW_COUNT][COL_COUNT];

        } Pixels1000;

        typedef struct {

            Pixels500 distances;

            Pixels500 amplitudes;

        } SubPics;

        typedef union {

            SubPics subPictures;

            Pixels1000 wholePicture;

        } Pic;

        typedef T ValueType;

    };

    typedef iris::dist500::Pic* PicPtr;

public:

    typedef Dist500ValueMatrix<signed short>::Pic Dist500SignedShortMatrix;

    typedef Dist500ValueMatrix<double>::Pic Dist500DoubleMatrix;

    typedef Dist500ValueMatrix<unsigned long>::Pic Dist500UnsignedLongMatrix;

    typedef Dist500ValueMatrix<bool>::Pic Dist500BoolMatrix;

protected:

    template <class T> void assignMatrix(T& dest, const T& src) {
        memcpy(dest.wholePicture.linear, src.wholePicture.linear, sizeof(dest.wholePicture.linear));
    }

    template <class T> void zeroValues(T& dest) {
        memset(dest.wholePicture.linear, 0, sizeof(dest.wholePicture.linear));
    }

    /**
     * Holds the value sums
     */
    Dist500UnsignedLongMatrix sums;

    /**
     * Holds the valid (non-saturated) picture counts
     */
    Dist500UnsignedLongMatrix counts;

    /**
     * Holds the invalid (saturated) picture counts
     */
    Dist500UnsignedLongMatrix satCounts;

    /**
     * Holds the minimum values
     */
    Dist500SignedShortMatrix minima;

    /**
     * Holds the maximum values
     */
    Dist500SignedShortMatrix maxima;

    /**
     * Holds the (arithmetic) mean values
     */
    Dist500DoubleMatrix means;

    /**
     * Holds the standard deviation values
     *
     * @see setSavePictures
     */
    Dist500DoubleMatrix deviations;

    /**
     * Flag indicating the means' computation status.
     * <code>true</code> = already computed, <code>false</code> = yet uncomputed
     */
    bool meansKnown;

    /**
     * Flag indicating the standard deviations' computation status.
     * <code>true</code> = already computed, <code>false</code> = yet uncomputed
     */
    bool deviationsKnown;

    /**
     * Holds the number of processed pictures
     */
    unsigned int dataCount;

    /**
     * Typedef for a vector of pictures "matrices"
     */
    typedef std::vector<PicPtr> PicPtrVector;

    /**
     * Holds the vector of processed pictures
     *
     * @see setSavePictures
     */
    PicPtrVector pictures;

    /**
     * (Re)computes the mean values (if necessary)
     */
    void computeMeans(void);

    /**
     * (Re)computes the standard deviation values (if necessary)
     */
    void computeDeviations(void);

    /**
     * Flag indicating if processed pictures are saved (eg for computation of
     * standard deviation).
     * <code>true</code> = saving active, <code>false</code> otherwise
     */
    bool activeSavePictures;

    //bool activeAutoRecompute;

    /**
     * Signals the availability of new data within the attached source.
     * This callback method is abstract. Derived PictureSink classed therefore
     * need to implement it.
     *
     * @param picture Picture instance containing the new data
     * @param pictureIndex 0-based index of the picture if the total number of
     *        pictures is known, 0 otherwise
     * @param pictureIndexCount Total number of picture (0 if unknown)
     */
    void processNewPicture(iris::dist500::Picture* picture,
            unsigned long pictureIndex, unsigned long pictureIndexCount);

    iris::synchronization::Mutex mutex;

    bool locked;

    typedef std::list<PicPtr> PicPtrList;

    PicPtrList tempPictures;

    iris::synchronization::Mutex tempMutex;

public:

    void lockStatistics(void);

    void unlockStatistics(void);

    /**
     * Constructor
     */
    AggregatorV2(/*iris::dist500::PictureSource* source = 0*/);

    /**
     * Destructor
     */
    virtual ~AggregatorV2();

    /**
     * Resets the statistics and clears any previously saved pictures
     */
    void reset(void);

    /**
     * Processes the given picture (ie updates the statistics).
     * The picture will also be appended to the save list (if feature is
     * activated)
     *
     * @param values Pointer to picture
     *
     * @see setSavePictures
     */
    void processPicture(const iris::dist500::Pic* picture);

    /**
     * Returns the number of processed pictures
     *
     * @return Picture count
     */
    unsigned int getDataCount(void);

    /**
     * Returns the sum matrix
     *
     * @param buffer Receiving matrix
     */
    void getSums(Dist500UnsignedLongMatrix& buffer);

    /**
     * Returns the normal counts matrix
     *
     * @param buffer Receiving matrix
     */
    void getCounts(Dist500UnsignedLongMatrix& buffer);

    /**
     * Returns the saturation count matrix
     *
     * @param buffer Receiving matrix
     */
    void getSatCounts(Dist500UnsignedLongMatrix& buffer);

    /**
     * Returns the minima matrix
     *
     * @param buffer Receiving matrix
     */
    void getMinima(Dist500SignedShortMatrix& buffer);

    /**
     * Returns the maxima matrix
     *
     * @param buffer Receiving matrix
     */
    void getMaxima(Dist500SignedShortMatrix& buffer);

    /**
     * Returns the means matrix
     *
     * @param buffer Receiving matrix
     */
    void getMeans(Dist500DoubleMatrix& buffer);

    /**
     * Controls whether processed pictures are saved or note
     *
     * @param savePictures Control flag (<code>true</code> = save pictures,
     *        <code>false</code> = don't save pictures)
     *
     * @see getMeans
     */
    void setSavePictures(bool savePictures);

    /**
     * Returns the picture-saving status
     *
     * @return <code>true</code> if saving is active, <code>false</code>
     *         otherwise
     *
     * @see getMeans
     */
    bool savePictures(void);

    /**
     * Returns a stored picture by its index
     *
     * @param index Picture number (0 .. n-1)
     * @param buffer Receiving picture buffer
     *
     * @note Only available if "save pictures" feature is activated
     *
     * @see setSavePictures
     * @see getDataCount
     */
    void getPicture(unsigned int index, iris::dist500::Pic& buffer);

    /**
     * Returns the standard deviation matrix
     *
     * @param buffer Receiving matrix
     *
     * @note Only available if "save pictures" feature is activated
     *
     * @see setSavePictures
     */
    void getDeviations(Dist500DoubleMatrix& buffer);

}; // class Aggregator

} // namespace metrology

} // namespace iris

#endif // METROLOGY_AGGREGATOR_H
