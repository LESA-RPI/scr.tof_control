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

#ifndef DIST500_FLASHCONTROLLER_H
#define DIST500_FLASHCONTROLLER_H

// iris includes
#include "iris/Common.h"
#include "iris/drivers/Sensor.h"
#include "iris/dist500/Dist500Base.h"
#include "iris/UipTypes.h"

namespace iris {

namespace dist500 {

/**
 * Implements Flash access functions provided by the DIST500 sensor
 * There are two groups of methods that are used by a firmware release. Beginning from release 3.X, a different
 * flash layout is used and updates are made resilient against power loss or other accidents.
 * Any release 1.X or 2.X supports the methods eraseMemory, readMemory, writeMemory.
 * Any release 3.X supports the methods eraseFirmware, readFirmware, writeFirmware, switchFirmware
 */
class SENSORAPI FlashController: virtual public Dist500Base {

public:

    /**
     * Constructor
     *
     * @param sensor
     */
    FlashController(iris::drivers::Sensor& sensor);

    /**
     * Destructor
     */
    virtual ~FlashController();

    /**
     * Erases a Flash sector
     *
     * @param address Start address of Flash sector
     * @see readMemory, writeMemory
     * @note  Used in firmware release 2. Release 3 uses writeFirmware, readFirmware, eraseFirmware, switchFirmware
     *
     * @return Operation result
     */
    SENSOR_RESULT eraseMemory(unsigned long address);

    /**
     * Writes data into the Flash
     *
     * @param address Start address of target space in Flash
     *        memory (needs to be a multiple of 2)
     * @param buffer Pointer to source bytes
     * @param byteCount Number of bytes to be written (needs
     *        to be a multiple of 2)
     * @param verify Verification flag (<code>true</code> turns
     *        it on, <code>false</code> skips it)
     * @see readMemory, eraseMemory
     * @note  Used in firmware release 2. Release 3 uses writeFirmware, readFirmware, eraseFirmware, switchFirmware
     *
     * @return Operation result
     */
    SENSOR_RESULT writeMemory(unsigned long address, char* buffer, unsigned short byteCount, bool verify = false);

    /**
     * Reads data from the flash
     *
     * @param address Start address of source space in Flash
     *        memory (needs to be a multiple of 2)
     * @param buffer Pointer to destination byte buffer
     * @param byteCount Number of bytes to be read (needs
     *        to be a multiple of 2)
     * @see writeMemory, eraseMemory
     * @note  Used in firmware release 2. Release 3 uses writeFirmware, readFirmware, eraseFirmware, switchFirmware
     *
     * @return Operation result
     */
    SENSOR_RESULT readMemory(unsigned long address, char* buffer, unsigned short byteCount);
                
    /**
     * @brief readFirmware Reads the specified firmwareType 
     * @param messageCount Running index in a batch of messages; This is to not confuse replies when a reply is missing.
     * @param firmwareType Which type of firmware to read.
     * @param readBackup Here 0 (0x0) means read current, 1 (0x1) means read backup
     * @param byteOffset The offset in the sensor firmware to read from
     * @param buffer A buffer to write to; must provide space for numberOfBytes bytes
     * @param numberOfBytes How many bytes to read; A safe maximum for a UIP frame is 1024 bytes.
     * @note  Used in firmware release 3.

     * @return 
     */
    SENSOR_RESULT readFirmware(uip::ushort messageCount, iris::uip::firmware_type firmwareType, iris::uip::backup_type backupType, uip::ulong byteOffset, iris::uip::uchar* buffer, uip::ushort numberOfBytes);
    
    /**
     * @brief writeFirmware Writes the specified firmwareType. Always writes to backup. To activate requires switchFirmware.
     * @param messageCount Running index in a batch of messages; intended to cross-check with the reply that all sent packages arrived at the sensor.
     * @param firmwareType Which type of firmware's content is being sent.
     * @param byteOffset The offset in the sensor firmware to write to (for each packet should be incremented by last numberOfBytes in the batch)
     * @param buffer A buffer to write from; must contain numberOfBytes bytes
     * @param numberOfBytes How many bytes to write; A safe maximum for a UIP frame is 1024 bytes.
     * @note  Used in firmware release 3.
     * @return Operation result
     */
    SENSOR_RESULT writeFirmware(uip::ushort messageCount, iris::uip::firmware_type firmwareType, uip::ulong byteOffset, iris::uip::uchar* buffer, uip::ushort numberOfBytes);
    
    /**
     * @brief eraseFirmware Erases a backup firmware in the sensor. A related info block is erased also. Current firmware can not be deleted.
     * @param firmwareType Which type of firmware to erase.
     * @return Operation result
     * @note  Used in firmware release 3.
     */
    SENSOR_RESULT eraseFirmware(iris::uip::firmware_type firmwareType);

    /**
     * @brief switchFirmware Switches the specified type(s) of firmware.
     * @param uniqueRequestId A unique request id; necessary for cases where a message was lost and is repeated. The sensor will ignore that Id and not switch again (which would nullify the request). Set this to a (sufficiently) unique id.
     * @param firmwareFlagsCount Number of flags in the buffer firmwareTypeFlags
     * @param firmwareTypeFlags A buffer containing firmwareFlagsCount flags, whose valid values are a subset of iris::uip::firmware_type (InfoBlock* values excluded).
     * @note  Used in firmware release 3.
     * @return Operation result
     */
    SENSOR_RESULT switchFirmware(iris::uip::ulonglong uniqueRequestId, iris::uip::uchar firmwareFlagsCount, const iris::uip::firmware_type* firmwareTypeFlags);

}; // class FlashController

} // namespace dist500

} // namespace iris

#endif // DIST500_FLASHCONTROLLER_H
