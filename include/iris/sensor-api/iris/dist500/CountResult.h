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

#ifndef DIST500_COUNTRESULT_H
#define DIST500_COUNTRESULT_H

// STL includes
#include <string>

// iris includes
#include "iris/Common.h"
#include "iris/dist500/PictureBoundData.h"

namespace iris {

namespace dist500 {

/**
 * Encapsulates a count result
 */
class SENSORAPI CountResult: public PictureBoundData {

protected:

    /**
     * Holds the category ID
     */
    unsigned short category;

    /**
     * Holds the number of boarding passengers
     */
    unsigned short boarding;

    /**
     * Holds the number of alighting passengers
     */
    unsigned short alighting;

    bool singleEvent;

    std::string comment;

    unsigned int intervalIndex;

    unsigned int countIndex;

public:

    /**
     * Constructor
     *
     * @param pictureNumber Picture number (created by sensor)
     * @param timestamp Timestamp (created by sensor)
     * @param category Caegory ID
     * @param boarding Number of boarding passengers
     * @param alighting Number of alighting passengers
     */
    CountResult(unsigned long pictureNumber, unsigned long long timestamp, unsigned short category, unsigned short boarding, unsigned short alighting);

    /*CountResult(const CountResult& other);*/

    /**
     * Returns the number of boarding passengers
     *
     * @return Boarding count
     */
    unsigned short getBoarding(void);

    /**
     * Returns the number of alighting passengers
     *
     * @return Alighting count
     */
    unsigned short getAlighting(void);

    /**
     * Returns the category ID
     *
     * @return Category ID
     */
    unsigned short getCategory(void);

    /**
     * No-arg constructor (needed for Qt signalling)
     */
    CountResult();

    void setCategory(const unsigned short category);

    void setBoarding(const unsigned short boarding);

    void setAlighting(const unsigned short alighting);

    bool isSingleEvent(void);

    void markAsSingleEvent(void);

    void markAsRegularCount(void);

    std::string getComment(void) const;

    unsigned int getIntervalIndex(void) const;

    unsigned int getCountIndex(void) const;

    void setCommand(const std::string& comm);

    void setIntervalIndex(const unsigned int idx);

    void setCountIndex(const unsigned int idx);

}; // class CountResult

} // namespace dist500

} // namespace iris

#endif // DIST500_COUNTRESULT_H
