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

#ifndef DIST500_DOORSTATE_H
#define DIST500_DOORSTATE_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/PictureBoundData.h"

namespace iris {

namespace dist500 {

/**
 * Encapsulates a door state as a class.
 * @see DoorController::getDoorState
 */
class SENSORAPI DoorState : public PictureBoundData {

protected:

    /**
     * Holds the door number
     */
    unsigned short door;

    /**
     * Holds the function area
     */
    unsigned short functionArea;

    /**
     * Holds the left wing's opening percentage
     */
    unsigned char left;

    /**
     * Holds the right wing's opening percentage
     */
    unsigned char right;

public:

    /**
     * Constructor
     *
     * @param pictureNumber
     * @param timestamp
     * @param door
     * @param functionArea
     * @param left
     * @param right
     */
    DoorState(unsigned long pictureNumber, unsigned long long timestamp, unsigned short door, unsigned short functionArea, unsigned char left, unsigned char right);

    /*DoorState(const DoorState& other);*/

    /**
     * No-arg constructor (needed for Qt signalling)
     */
    DoorState();

    /**
     * Returns the door number
     *
     * @return Door number
     */
    unsigned short getDoor(void) const;

    /**
     * Returns the function area
     *
     * @return Function area
     */
    unsigned short getFunctionArea(void) const;

    /**
     * Returns the left wing's opening percentage
     *
     * @return Left wing's opening percentage
     */
    unsigned char getLeft(void) const;

    /**
     * Returns the right wing's opening percentage
     *
     * @return Right wing's opening percentage
     */
    unsigned char getRight(void) const;

    /**
     * @brief setLeft
     * @param state
     */
    void setLeft(unsigned char state);

    /**
     * @brief setRight
     * @param state
     */
    void setRight(unsigned char state);

    /**
     * @brief setFunctionArea
     * @param fa
     * @see SensorInfo::getFunctionArea
     */
    void setFunctionArea(unsigned short fa);

    /**
     * @brief setDoor
     * @param doorNum
     * @see SensorInfo::getDoorNumber
     */
    void setDoor(unsigned short doorNum);

}; // class DoorState

} // namespace dist500

} // namespace iris

#endif // DIST500_DOORSTATE_H
