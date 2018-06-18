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

#ifndef DIST500_REGISTERVALUES_H
#define DIST500_REGISTERVALUES_H

// iris includes
#include "iris/Common.h"
#include "iris/dist500/PictureBoundData.h"

namespace iris {

namespace dist500 {

/**
 * Encapsulates a set of FPGA register values.
 */
class SENSORAPI RegisterValues: public PictureBoundData {

protected:

    /**
     * Maximum number of registers
     */
    enum { MaxRegisters = 32 };

    /**
     * Holds the number of registers in the dataset
     */
    unsigned short numRegisters;

    /**
     * Holds the register values
     */
    unsigned short registerValues[MaxRegisters];

    /**
     * Holds the register numbers
     */
    unsigned short registerNumbers[MaxRegisters];

public:

    /**
     * Constructor
     *
     * @param pictureNumber Picture number (created by sensor)
     * @param timestamp Timestamp (created by sensor)
     * @param numRegisters Number of register values
     * @param registerNumbers Array containing the register numbers
     * @param registerValues Array containing the register values
     */
    RegisterValues(unsigned long pictureNumber, unsigned long long timestamp, unsigned short numRegisters, unsigned short* registerNumbers, unsigned short* registerValues);

    /*RegisterValues(const RegisterValues& other);*/

    /**
     * No-arg constructor (needed for Qt signalling)
     */
    RegisterValues();

    /**
     * Returns the number of registers
     *
     * @return Number of registers
     */
    unsigned short getNumRegisters(void);

    /**
     * Returns a register's number
     *
     * @param index 0-based index of register to be read
     *
     * @return Register number
     */
    unsigned short getRegisterNumber(unsigned short index);

    /**
     * Returns a register's value
     *
     * @param index 0-based index of register to be read
     *
     * @return Register value
     */
    unsigned short getRegisterValue(unsigned short index);

    void setRegisterValue(unsigned short index, unsigned short value);

    void setNumRegisters(unsigned short num);

    void setRegisterNumber(unsigned short index, unsigned short number);

}; // class RegisterValues

} // namespace dist500

} // namespace iris

#endif // DIST500_REGISTERVALUES_H
