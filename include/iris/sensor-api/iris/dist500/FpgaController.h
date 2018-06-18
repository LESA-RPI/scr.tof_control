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

#ifndef DIST500_FPGACONTROLLER_H
#define DIST500_FPGACONTROLLER_H

// iris includes
#include "iris/Common.h"
#include "iris/drivers/Sensor.h"
#include "iris/dist500/Dist500Base.h"

namespace iris {

namespace dist500 {

/**
 * Implements FPGA related functions within the DIST500 firmware
 */
class SENSORAPI FpgaController: virtual public Dist500Base {

public:

    /**
     * Constructor
     *
     * @param sensor Sensor reference from driver framework
     */
    FpgaController(iris::drivers::Sensor& sensor);

    /**
     * Destructor
     */
    virtual ~FpgaController();

    /**
     * FPGA register number definitions
     */
    typedef enum {

        /**
         * Command register (0)
         */
        CommandRegister,

        /**
         * Status register (1)
         */
        StatusRegister,

        /**
         * Mode register (2)
         */
        ModeRegister,

        /**
         * Firmware register (3)
         */
        FirmwareRegister,

        /**
         * Threshold (low) register (4)
         */
        ThresholdLowRegister,

        /**
         * Threshold (high) register (5)
         */
        ThresholdHighRegister,

        /**
         * Saturation (low) register (6)
         */
        SaturationLowRegister,

        /**
         * Saturation (high) register (7)
         */
        SaturationHighRegister,

        /**
         * Distance offset register (8)
         */
        DistanceOffsetRegister,

        /**
         * Exposure time register (9)
         */
        ExposureTimeRegister,

        /**
         * Maximum temperature register (10)
         */
        MaxTemperatureRegister,

        /**
         * Current temperature register (11)
         */
        CurrentTemperatureRegister,

        /**
         * Status bit selection register (12)
         */
        StatusBitSelectionRegister,

        /**
         * Picture period register (13)
         */
        PicturePeriodRegister,

        /**
         * Illumination control register (14)
         */
        IlluminationControlRegister,

        /**
         * Debug mode register (31)
         */
        DebugModeRegister = 31

    } FpgaRegister;

    /**
     * Returns the current value of an FPGA register
     *
     * @param registr
     * @param buffer
     *
     * @return Operation result
     *
     * @note "registr" is used because "register" is a C++ keyword
     */
    SENSOR_RESULT getFpgaRegister(const FpgaRegister registr, unsigned char &buffer);

    /**
     * Sets the value of an FPGA register
     *
     * @param registr
     * @param value
     *
     * @return Operation result
     *
     * @note "registr" is used because "register" is a C++ keyword
     */
    SENSOR_RESULT setFpgaRegister(const FpgaRegister registr, const unsigned char value);

    /**
     * Sets the value of the "Command" FPGA register
     *
     * @param command New value
     *
     * @return Operation result
     */
    SENSOR_RESULT setCommandRegister(const unsigned char command);

    /**
     * Gets the value of the "Status" FPGA register
     *
     * @param status Buffer for current value
     *
     * @return Operation result
     */
    SENSOR_RESULT getStatusRegister(unsigned char &status);

    /**
     * Gets the value of the "Mode" FPGA register
     *
     * @param mode Buffer for current value
     *
     * @return Operation result
     */
    SENSOR_RESULT getModeRegister(unsigned char &mode);

    /**
     * Sets the value of the "Mode" FPGA register
     *
     * @param mode New value
     *
     * @return Operation result
     */
    SENSOR_RESULT setModeRegister(const unsigned char mode);

    /**
     * Gets the value of the "Firmware" FPGA register
     *
     * @param version Buffer for value
     *
     * @return Operation result
     */
    SENSOR_RESULT getFirmwareRegister(unsigned char &version);

    /**
     * Gets the value of the "Threshold" FPGA register pair
     *
     * @param threshold Buffer for current value
     *
     * @return Operation result
     */
    SENSOR_RESULT getThresholdRegister(unsigned short &threshold);

    /**
     * Sets the value of the "Threshold" FPGA register pair
     *
     * @param threshold New value
     *
     * @return Operation result
     */
    SENSOR_RESULT setThresholdRegister(const unsigned short threshold);

    /**
     * Gets the value of the "Saturation" FPGA register pair
     *
     * @param saturation Buffer for current value
     *
     * @return Operation result
     */
    SENSOR_RESULT getSaturationRegister(unsigned short &saturation);

    /**
     * Sets the value of the "Saturation" FPGA register pair
     *
     * @param saturation New value
     *
     * @return Operation result
     */
    SENSOR_RESULT setSaturationRegister(const unsigned short saturation);

    /**
     * Gets the value of the "Distance Offset" FPGA register
     *
     * @param offset Buffer for current value
     *
     * @return Operation result
     */
    SENSOR_RESULT getDistanceOffsetRegister(unsigned char &offset);

    /**
     * Sets the value of the "Distance Offset" FPGA register
     *
     * @param offset New value
     *
     * @return Operation result
     */
    SENSOR_RESULT setDistanceOffsetRegister(const unsigned char offset);

    /**
     * Gets the value of the "Exposure Time" FPGA register
     *
     * @param exposure Buffer for current value
     *
     * @return Operation result
     */
    SENSOR_RESULT getExposureTimeRegister(unsigned char &exposure);

    /**
     * Sets the value of the "Exposure Time" FPGA register
     *
     * @param exposure New value
     *
     * @return Operation result
     */
    SENSOR_RESULT setExposureTimeRegister(unsigned char exposure);

    /**
     * Gets the value of the "Max Temperature" FPGA register
     *
     * @param temperature Buffer for current value
     *
     * @return Operation result
     */
    SENSOR_RESULT getMaxTemperatureRegister(unsigned char &temperature);

    /**
     * Sets the value of the "Max Temperature" FPGA register
     *
     * @return Operation result
     */
    SENSOR_RESULT setMaxTemperatureRegister(const unsigned char temperature);

    /**
     * Gets the value of the "Current Temperature" FPGA register
     *
     * @param temperature Buffer for current value
     *
     * @return Operation result
     */
    SENSOR_RESULT getCurrentTemperatureRegister(unsigned char &temperature);

    /**
     * Gets the value of the "Status Bit Selection" FPGA register
     *
     * @param selection Buffer for current value
     *
     * @return Operation result
     */
    SENSOR_RESULT getStatusBitSelectionRegister(unsigned char &selection);

    /**
     * Sets the value of the "Status Bit Selection" FPGA register
     *
     * @param selection New value
     *
     * @return Operation result
     */
    SENSOR_RESULT setStatusBitSelectionRegister(const unsigned char selection);

    /**
     * Gets the value of the "Illumination Control" FPGA register
     *
     * @param illumination Buffer for current value
     *
     * @return Operation result
     */
    SENSOR_RESULT getIlluminationControlRegister(unsigned char &illumination);

    /**
     * Sets the value of the "Illumination Control" FPGA register
     *
     * @param illumination New value
     *
     * @return Operation result
     */
    SENSOR_RESULT setIlluminationControlRegister(const unsigned char illumination);

    /**
     * Gets the value of the "Picture Period" FPGA register
     *
     * @param period Buffer for current value
     *
     * @return Operation result
     */
    SENSOR_RESULT getPicturePeriodRegister(unsigned char &period);

    /**
     * Sets the value of the "Picture Period" FPGA register
     *
     * @param period New value
     *
     * @return Operation result
     */
    SENSOR_RESULT setPicturePeriodRegister(unsigned char period);

    /**
     * Gets the value of the "Debug Mode" FPGA register
     *
     * @param debug Buffer for current value
     *
     * @return Operation result
     */
    SENSOR_RESULT getDebugModeRegister(unsigned char &debug);

    /**
     * Sets the value of the "Debug Mode" FPGA register
     *
     * @param debug New value
     *
     * @return Operation result
     */
    SENSOR_RESULT setDebugModeRegister(const unsigned char debug);

    /**
     * Uploads an UFF movie into the sensor for simulation
     *
     * @param filename Name of UFF file
     * @param picCount Number of uploaded pictures (may be less than the
     *        picture count of the UFF file if simulation RAM is too small)
     *
     * @return Operation result
     * @deprecated The movie memory is disabled in current firmware. Simulation is now performed frame-by-frame.
     */
    SENSOR_RESULT uploadUffMovie(const std::string& filename, int& picCount);

    /**
     * Uploads a full single Picture into the sensor
     * @param picNumber
     * @param timestamp
     * @param picture
     *
     * @return
     */
    SENSOR_RESULT uploadFullSingleUffMoviePicture(unsigned long picNumber, unsigned long long timestamp, unsigned short *picture,const char numberOfDoors, const iris::uip::door_status* doorState, bool ledOn);

protected:

    /**
     * Prepares the upload of an UFF movie for simulation
     *
     * @param picCount Number of pictures
     *
     * @return Operation result
     * @deprecated The movie memory is disabled in current firmware. Simulation is now performed frame-by-frame.
     */
    SENSOR_RESULT prepareMovieUpload(int& picCount);

    /**
     * Uploads a movie (sub-)picture to the sensor
     *
     * @param subPicNo Number of current sub-picture (1-based)
     * @param subPicTotal Total sub-pics per cycle
     * @param subPicType Type of sub-picture (D: distance, A: amplitude)
     * @param picNumber Picture number
     * @param timestamp Timestamp
     * @param pixels Pointer to picture data
     *
     * @return Operation result
     */
    SENSOR_RESULT uploadMoviePicture(unsigned char subPicNo, unsigned char subPicTotal, iris::uip::sub_pic_type subPicType,
                                     unsigned long picNumber, unsigned long long timestamp, unsigned short* pixels,
                                     const char numberOfDoors, const iris::uip::door_status* doorState, bool ledOn);

    /**
     * Activates the movie by resetting the simulation
     *
     * @return Operation result
     * @deprecated The movie memory is disabled in current firmware. Simulation is now performed frame-by-frame.
     */
    SENSOR_RESULT activateMovie(void);

}; // class FpgaController

} // namespace dist500

} // namespace iris

#endif // DIST500_FPGACONTROLLER_H
