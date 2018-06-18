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

#ifndef METROLOGY_AGGREGATOR_H
#define METROLOGY_AGGREGATOR_H

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
class SENSORAPI Aggregator: public iris::dist500::PictureSink {

protected:

    /**
     * Total number of values per picture (1000 = 500 pixels x 2 sub-pics)
     */
    enum {
        PIXEL_COUNT = 1000
    };

    /**
     * Unsigned short (array) pointer type
     */
    typedef unsigned short *UnsignedShortMatrix;

    /**
     * Double value "matrix" with 1000 elements
     */
    typedef double DoubleMatrix[PIXEL_COUNT];

    /**
     * Bool value "matrix" with 1000 elements
     */
    typedef bool BoolMatrix[PIXEL_COUNT];

    /**
     * Holds the value sums
     */
    unsigned long sums[PIXEL_COUNT];

    /**
     * Holds the valid (non-saturated) picture counts
     */
    unsigned long counts[PIXEL_COUNT];

    /**
     * Holds the invalid (saturated) picture counts
     */
    unsigned long satCounts[PIXEL_COUNT];

    /**
     * Holds the minimum values
     */
    unsigned short minima[PIXEL_COUNT];

    /**
     * Holds the maximum values
     */
    unsigned short maxima[PIXEL_COUNT];

    /**
     * Holds the (arithmetic) mean values
     */
    double means[PIXEL_COUNT];

    /**
     * Holds the standard deviation values
     *
     * @see setSavePictures
     */
    double deviations[PIXEL_COUNT];

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
    typedef std::vector<UnsignedShortMatrix> UnsignedShortMatrixVector;

    /**
     * Holds the vector of processed pictures
     *
     * @see setSavePictures
     */
    UnsignedShortMatrixVector pictures;

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

    typedef std::list<UnsignedShortMatrix> UnsignedShortMatrixList;

    UnsignedShortMatrixList tempPictures;

    iris::synchronization::Mutex tempMutex;

public:

    void lockStatistics(void);

    void unlockStatistics(void);

    /**
     * Constructor
     */
    Aggregator();

    /**
     * Destructor
     */
    virtual ~Aggregator();

    /**
     * Resets the statistics and clears any previously saved pictures
     */
    void reset(void);

    /**
     * Processes the given picture (ie updates the statistics).
     * The picture will also be appended to the save list (if feature is
     * activated)
     *
     * @param values Pointer to picture "matrix"
     *
     * @see setSavePictures
     */
    void processPicture(unsigned short* values);

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
    void getSums(unsigned long *buffer);

    /**
     * Returns the normal counts matrix
     *
     * @param buffer Receiving matrix
     */
    void getCounts(unsigned long *buffer);

    /**
     * Returns the saturation count matrix
     *
     * @param buffer Receiving matrix
     */
    void getSatCounts(unsigned long *buffer);

    /**
     * Returns the minima matrix
     *
     * @param buffer Receiving matrix
     */
    void getMinima(signed short *buffer);

    /**
     * Returns the maxima matrix
     *
     * @param buffer Receiving matrix
     */
    void getMaxima(signed short *buffer);

    /**
     * Returns the means matrix
     *
     * @param buffer Receiving matrix
     */
    void getMeans(double *buffer);

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
    void getPicture(unsigned int index, unsigned short* buffer);

    /**
     * Returns the standard deviation matrix
     *
     * @param buffer Receiving matrix
     *
     * @note Only available if "save pictures" feature is activated
     *
     * @see setSavePictures
     */
    void getDeviations(double *buffer);

}; // class Aggregator

} // namespace metrology

} // namespace iris

#endif // METROLOGY_AGGREGATOR_H
