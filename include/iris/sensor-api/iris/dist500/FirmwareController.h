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

#ifndef DIST500_FIRMWARECONTROLLER_H
#define DIST500_FIRMWARECONTROLLER_H

// STL includes
#include <list>

// iris includes
#include "iris/Common.h"
#include "iris/dist500/FlashController.h"
#include "iris/dist500/SensorInfoProvider.h"
#include "iris/configuration/Configuration.h"
#include "iris/hexfiles/HexFileStreamReader.h"

namespace iris {

namespace legacy{
    struct _EMBEDDED_FILE;
    class Dist500FirmwareContainerDecoder;
}

namespace dist500 {

class Dist500;

/**
 * RESTART_STEPS
 */
const unsigned int RESTART_STEP = 1;

/**
 * CONFIG_STEPS
 */
const unsigned int CONFIG_STEPS = 5;

/**
 * GROUP_CONFIG_STEP
 */
const unsigned int GROUP_CONFIG_STEP = 1;

/**
 * Container update state
 */
typedef enum{
    UNDEFINED_STATE = 0,
    PERFORM_APPLICATION_UPDATE,
    PERFORM_APPLICATION_VERIFY,
    PERFORM_COMMUNICATION_UPDATE,
    PERFORM_COMMUNICATION_VERIFY,
    PERFORM_FIRST_FPGA_UPDATE,
    PERFORM_FIRST_FPGA_VERIFY,
    PERFORM_SECOND_FPGA_UPDATE,
    PERFORM_SECOND_FPGA_VERIFY,
    PERFORM_SENSOR_RESTART,
    PERFORM_READ_CONFIGURATION,
    PERFORM_WRITE_CONFIGURATION,
    PERFORM_SAVE_CONFIGURATION,
    PERFORM_CHANGE_CONFIGURATION
} CONTAINER_UPDATE_STATE;

/**
 * Callback for firmware updates
 *
 * @param userData User-defined additional parameter
 * @param step Current step
 * @param totalSteps Total number of steps
 * @param stepPercentage Progress within current step
 * @param totalPercentage Total progress
 */
typedef void (*UPDATE_CALLBACK)(void* userData, unsigned int step,
        unsigned int totalSteps, double stepPercentage, double totalPercentage);

/**
 * Callback for firmware updates with container file
 *
 * @param userData User-defined additional parameter
 * @param sensor
 * @param updateState
 * @param containerStep Current container update step
 * @param containerTotalSteps Total container update steps
 * @param stepPercentage Progress within current step
 * @param totalPercentage Total progress
 */
typedef void (*CONTAINER_UPDATE_CALLBACK) (void* userData, iris::dist500::Dist500* sensor,
        CONTAINER_UPDATE_STATE updateState, unsigned int containerStep, unsigned int containerTotalSteps,
        double stepPercentage, double totalPercentage);

/**
 * Implements DIST500 functions related to firmware and configuration data
 **/
class SENSORAPI FirmwareController: public FlashController, public SensorInfoProvider {

protected:

    #pragma pack(2)
    typedef struct {
        unsigned int Magic;
        unsigned int FirmwareSize;
        unsigned int FirmwareCRC;
        char FirmwareName[128];
        char FirmwareTimestamp[32];
        char UploadTimestamp[32];
        char UploadUser[32];
        char UploadComputer[32];
        char UploadAddress[32];
        char UploadApplication[32];
    } t_FirmwareInfo;
    #pragma pack()

    #pragma pack(2)
    typedef struct {
        t_FirmwareInfo firmwareInfo;
        unsigned int firmwareInfoCrc;
    } t_FirmwareInfoWithCRC;
    #pragma pack()

    #pragma pack(2)
    /**
     * Typedef for firmware release information
     */
    typedef struct {
      /**
       * Magic number
       */
      char Magic[32];

      /**
       * Firmware revision number
       */
      unsigned short Version;

      /**
       * Type of the firmware
       */
      char FirmwareType [16];
    } FirmwareReleaseInfo;
    #pragma pack()

    typedef std::list<int32_t> ListFpgaFilesContainerIndex;

    typedef struct {
        uint32_t hardwareRelease;
        ListFpgaFilesContainerIndex listFpgaFilesContainerIndex;
        iris::configuration::FirmwareGroup::DspFirmware dspFirmware;
        iris::configuration::FirmwareGroup::Version dspFirmwareVersion;
    } SensorInformation;

    typedef std::map<Dist500*, SensorInformation> SensorInformationMap;

    /**
     * Static (global) callback for hex file decoding
     *
     * @param userData User-defined additional parameter
     * @param address Address of line data
     * @param data Pointer to line data
     * @param len Number of bytes in line
     */
    static void _hexFileCallback(void* userData, const unsigned long address,
            const unsigned char* const data, const unsigned char len);

    /**
     * Callback (sensor-specific) for hex file decoding
     *
     * @param address Address of line data
     * @param data Pointer to line data
     * @param len Number of bytes in line*
     */
    void hexFileCallback(const unsigned long address,
            const unsigned char* const data, const unsigned char len);

    /**
     * Indicated whether addresses are to be evaluated (<code>true</code>)
     * or if data is to be copied to firmware buffer (<code>false</code>)
     *
     * @return Range detection flag
     */
    bool determineHexFileAddressRange;

    /**
     * Holds the minimum address in a hex file
     */
    unsigned long minHexFileAddress;

    /**
     * Holds the maximum address in a hex file
     */
    unsigned long maxHexFileAddress;

    /**
     * Buffer for firmware, only used temporarily (otherwise 0)
     */
    char* firmware;
    
    /**
     * @brief firmwareDecodedSize Stores length of binary data that was decoded from the Intel HEX file
     */
    unsigned long firmwareDecodedSize;

    /**
     * Updates a firmware part from the given .LDR file
     *
     * @param hexfileName Filename of the .LDR file containing the firmware
     * @param userData User-defined additional parameter
     * @param updateCallback Callback function for progress updates
     * @param application Flag indicating whether the application part is to
     *        be updated (<code>true</code>) or the bootloader part
     *        (<code>false</code>)
     * @param onlyWriteInfo Flag indicating whether to only update the
     *        firmware info block and leave the firmware itself untouched
     *        (<code>true</code> = info only, <code>false</code> = full update)
     *
     * @return Operation result
     */
    SENSOR_RESULT performFirmwarePartUpdate(const std::string& hexfileName,
            void* userData, UPDATE_CALLBACK updateCallback, bool application,
            bool onlyWriteInfo = false);

    // timestamp format: "Wed May 20 00:00:00 2000"
    SENSOR_RESULT performFirmwarePartUpdate(char* hexfileContents, const unsigned long hexfileSize,
            const std::string firmwareFilename, const std::string& firmwareTimestamp,
            void* userData, UPDATE_CALLBACK updateCallback, bool application,
            bool onlyWriteInfo = false);

    SENSOR_RESULT performFirmwarePartUpdate(iris::hexfiles::HexFileStreamReader& hex,
            const std::string& hexfileName, const std::string& firmwareTimestamp,
            void* userData, UPDATE_CALLBACK updateCallback, bool application,
            bool onlyWriteInfo = false);

    SENSOR_RESULT findBootloaderWatermark(bool& hasWatermark);

    SENSOR_RESULT performFirmwarePartVerification(hexfiles::HexFileStreamReader &hex,
            void* userData, UPDATE_CALLBACK verificationCallback, bool application);

    /**
     * @brief Resets all sensor configuration data with certain exceptions needed to
     *        enable default operation of sensor
     *
     * @param config Reference to sensor configuration data
     */
    static void resetToDefaultOperation(iris::configuration::Dist500Configuration& config);

    static const unsigned int MAX_FPGA_IMAGE_SIZE = 128 * 1024;
    static const unsigned int MAX_FPGA_BITFILE_SIZE = MAX_FPGA_IMAGE_SIZE + 1024;

    /**
     * Indicated whether addresses are to be evaluated (<code>true</code>)
     * or if data is to be copied to firmware buffer (<code>false</code>)
     *
     * @return Range detection flag
     */
    static bool determineHexFileReleaseInfoAddressRange;

    /**
     * Holds the minimum address in a hex file
     */
    static unsigned long minHexFileReleaseInfoAddress;

    /**
     * Holds the maximum address in a hex file
     */
    static unsigned long maxHexFileReleaseInfoAddress;

    /**
     * Buffer for firmware
     */
    static char* releaseInfoFirmware;

    /**
     * Static (global) callback for hex file decoding
     *
     * @param userData User-defined additional parameter
     * @param address Address of line data
     * @param data Pointer to line data
     * @param len Number of bytes in line
     */
    static void hexFileReleaseInfoCallback(void* userData, const unsigned long address,
            const unsigned char* const data, const unsigned char len);

public:

    /**
     * Container file update result codes
     */
    typedef enum {

        /**
         * Update OK
         */
        CONTAINER_UPDATE_PASSED = 0,

        /**
         * General failure
         */
        CONTAINER_UPDATE_FAILED,

        /**
         * Cannot open container file
         */
        CONTAINER_OPEN_FILE_FAILED,

        /**
         * Set working mode failed
         */
        CONTAINER_SET_WORKING_MODE_FAILED,

        /**
         * Incomplete sensor group
         */
        CONTAINER_GROUP_INCOMPLETE,

        /**
         * Application firmware update has failed
         */
        CONTAINER_APPLICATION_UPDATE_FAILED,

        /**
         * Application firmware verification has failed
         */
        CONTAINER_APPLICATION_VERIFY_FAILED,

        /**
         * Communication firmware update has failed
         */
        CONTAINER_COMMUNICATION_UPDATE_FAILED,

        /**
         * Communication firmware verification has failed
         */
        CONTAINER_COMMUNICATION_VERIFY_FAILED,

        /**
         * FPGA firmware update has failed
         */
        CONTAINER_FPGA_UPDATE_FAILED,

        /**
         * First FPGA firmware update has failed
         */
        CONTAINER_FIRST_FPGA_UPDATE_FAILED,

        /**
         * Second FPGA firmware update has failed
         */
        CONTAINER_SECOND_FPGA_UPDATE_FAILED,

        /**
         * First FPGA firmware verification has failed
         */
        CONTAINER_FIRST_FPGA_VERIFY_FAILED,

        /**
         * Second FPGA firmware verification has failed
         */
        CONTAINER_SECOND_FPGA_VERIFY_FAILED,

        /**
         * Sensor restart has failed
         */
        CONTAINER_RESTART_FAILED,

        /**
         * Reading the configuration data has failed
         */
        CONTAINER_READ_CONFIGURATION_FAILED,

        /**
         * Changing the configuration data has failed
         */
        CONTAINER_CHANGE_CONFIGURATION_FAILED,

        /**
         * Getting update parameter from container file failed
         */
        CONTAINER_GET_UPDATE_PARAMETER_FAILED,

        /**
         * Writing configuration data failed
         */
        CONTAINER_WRITE_CONFIG_FAILED,

        /**
         * Saving the configuration data failed
         */
        CONTAINER_SAVE_CONFIG_FAILED,

        /**
         * The container file has unsupported data contents
         */
        UNSUPPORTED_CONTAINER_FILE,

        /**
         * One or more fpga image could not be read
         */
        CONTAINER_READ_FPGA_IMAGE_FAILED,

        /**
         * The container file has a wrong number of fpga images
         */
        CONTAINER_FPGA_IMAGE_MISMATCH,

        /**
         * Restore the configuration data from flash has failed
         */
        CONTAINER_RESTORE_CONFIGURATION_FROM_FLASH_FAILED,

        /**
         *
         */
        CONTAINER_GET_PARAMETER_FAILED


    } CONTAINER_UPDATE_RESULT;

    /**
     * Container paramter update result codes
     */
    typedef enum {

        /**
         * Parameter value not valid in the container file.
         * Parameter has the default value
         */
        CONTAINER_WRONG_PARAMETER_VALUE,

        /**
         * The Parameter is unknown
         */
        CONTAINER_UNKNOWN_PARAMETER,

        /**
         * The Parameter is unknown for the sensor
         */
        CONTAINER_UNKNOWN_SENSOR_PARAMETER,

        /**
         * Parameter could not be written
         */
        CONTAINER_PARAMETER_NOT_WRITE,

        /**
         * Parameter has the wrong update state and could not been updated
         */
        CONTAINER_PARAMETER_WRONG_UPDATE_STATE

    } CONTAINER_PARAMETER_RESULT;

    /**
     * Firmware information for skip list
     */
    typedef enum {
        APPLICATION_FIRMWARE,
        COMMUNICATION_FIRMWARE,
        FPGA1_FIRMWARE,
        FPGA2_FIRMWARE
    } SensorFirmware;

    /**
     * Result of the query if the firmware matches the Hardware.
     */
    typedef enum {
        /**
         * Firmware fits the hardware
         */
        FIRWARE_CHECK_PASSED,

        /**
         * General check failure
         */
        FIRWARE_CHECK_FAILED,

        /**
         * No valid file extension found
         */
        NO_VALID_FILE_EXTENSION,

        /**
         * Open the container file failed
         */
        CANNOT_OPEN_CONTAINER,

        /**
         * No application file found in the container file
         */
        NO_APPLICATION_FOUND,

        /**
         * Decode the firmware file failed
         */
        CANNOT_DECODE_HEXFILE,

        /**
         * Address range of the firmware file is wrong
         */
        HEXFILE_ADDRESS_RANGE_FAULTY,

        /**
         * Allocate memory for firmware file failed
         */
        ALLOC_MEMORY_FAILED,

        /**
         * Operation is failed because no iris authentication is present
         */
        NO_IRIS_AUTHENTICATION,

        /**
         * No firmware file was found
         */
        NO_LDR_FILE_FOUND,

        /**
         * Firmware version can not be read from the file name.
         */
        CANNOT_READ_FIRMWARE_VERSION,

        /**
         * Message verification failed.
         */
        CHECK_MESSAGE_SUPPORT_FAILED,

        /**
         * Read revision code from sensor failed
         */
        GET_REVISION_CODE_FAILED,

        /**
         * Revision code of the sensor is unknown
         */
        UNKNOWN_REVISION_CODE,

        /**
         * Firmware does not match the hardware
         */
        FIRMWARE_NOT_MATCH_TO_HARDWARE

    } FirmwareFitHardwareResult;

    /**
     * @brief Dist500List
     */
    typedef iris::dist500::Dist500List Dist500List;

    /**
     * Typedef for a parameter update result
     */
    typedef struct _ParameterUpdateInformation{
        /**
         * Parameter group id
         */
        unsigned short groupId;

        /**
         * Parameter id
         */
        unsigned short paramId;

        /**
         * Parameter update result
         */
        CONTAINER_PARAMETER_RESULT parameterResult;

        /**
         * Constructor
         */
        _ParameterUpdateInformation();

        /**
         * Copy constructor
         */
        _ParameterUpdateInformation(const _ParameterUpdateInformation& other);

        /**
         * Assignment operator
         */
        _ParameterUpdateInformation& operator = (const _ParameterUpdateInformation& other);
    }ParameterUpdateInformation;

    typedef std::list<SensorFirmware> FirmwareSkippedList;
    typedef std::list<ParameterUpdateInformation> ParameterUpdateInformationList;

    /**
     * Typedef for a container update information
     */
    typedef struct _UpdateInformation{
        /**
         * List of firmware that already was in the sensor and was skipped
         * during the update.
         */
        FirmwareSkippedList firmwareSkippedList;

        /**
         * Container update result code
         */
        CONTAINER_UPDATE_RESULT updateResultCode;

        /**
         * List of parameter update results
         */
        ParameterUpdateInformationList parameterUpdateInformation;

        /**
         * Constructor
         */
        _UpdateInformation();

        /**
         * Copy Constructor
         */
        _UpdateInformation(const _UpdateInformation& other);

        /**
         * Assignment operator
         */
        _UpdateInformation& operator = (const _UpdateInformation& other);

    } UpdateInformation;

    /**
     * Maps sensor instances to container update information
     */
    typedef std::map<iris::dist500::Dist500*, UpdateInformation> UpdateResultMap;

    /**
     * Maps sensor instances to firmware fit hardware result
     */
    typedef std::map<iris::dist500::Dist500*, FirmwareFitHardwareResult> FirmwareFitHardwareResultMap;

    /**
     * @brief Updates firmware and parameter from the given .D5FC file
     *
     * @param containerFilename Filename of the .D5FC file containing the
     *        firmware and parameter
     * @param resultMap Map receiving the update result for every sensor
     * @param checkSensorConsistency  Check consistency from group sensors
     *        <code>true</code> = all sensors of a group must be included in
     *        the List and present, <code>false</code> = no check
     *        It is strongly recommended to set this parameter to true.
     *        Only set to false if you know what you are doing.
     * @param userData User-defined additional parameter
     * @param containerUpdateCallback Callback function for progress updates
     *
     * @return Operation result
     *         <code>true</code> = Update for all sensors passed,
     *         <code>false</code> = Update for at least one sensor failed
     */
    bool performContainerUpdate(const std::string& containerFilename, UpdateResultMap& resultMap,
            bool checkSensorConsistency = true, void* userData = 0,
            CONTAINER_UPDATE_CALLBACK containerUpdateCallback = 0);

    /**
     * @brief Updates firmware and parameter from the given .D5FC file
     *
     * @param containerFilename Filename of the .D5FC file containing the
     *        firmware and parameter
     * @param remainingGroupSensors List of slave sensors
     * @param resultMap Map receiving the update result for every sensor
     * @param checkSensorConsistency  Check consistency from group sensors
     *        <code>true</code> = all sensors of a group must be included in
     *        the List and present, <code>false</code> = no check
     *        It is strongly recommended to set this parameter to true.
     *        Only set to false if you know what you are doing.
     * @param userData User-defined additional parameter
     * @param containerUpdateCallback Callback function for progress updates
     *
     * @return Operation result
     *         <code>true</code> = Update for all sensors passed,
     *         <code>false</code> = Update for at least one sensor failed
     */
    bool performContainerUpdate(const std::string& containerFilename, Dist500List& remainingGroupSensors,
            UpdateResultMap& resultMap, bool checkSensorConsistency = true,
            void* userData = 0, CONTAINER_UPDATE_CALLBACK containerUpdateCallback = 0);

    /**
     * @brief Updates firmware and parameter from the given .D5FC file
     *
     * @param containerFilename Filename of the .D5FC file containing the
     *        firmware and parameter
     * @param remainingGroupSensors List of slave sensors
     * @param resultMap Map receiving the update result for every sensor
     * @param checkSensorConsistency Check consistency from group sensors
     *        <code>true</code> = all sensors of a group must be included in
     *        the List and present, <code>false</code> = no check
     *        It is strongly recommended to set this parameter to true.
     *        Only set to false if you know what you are doing.
     * @param defaultValues Default values Flag
     *        <code>true</code> = Before the parameter update, all parameters
     *        get their default value, <code>false</code> = no default values
     * @param userData User-defined additional parameter
     * @param containerUpdateCallback Callback function for progress updates
     *
     * @return Operation result
     *         <code>true</code> = Update for all sensors passed,
     *         <code>false</code> = Update for at least one sensor failed
     */
    bool performContainerUpdateDefaults(const std::string& containerFilename, Dist500List& remainingGroupSensors,
            UpdateResultMap& resultMap, bool checkSensorConsistency, bool defaultValues,
            void* userData = 0, CONTAINER_UPDATE_CALLBACK containerUpdateCallback = 0);

    static bool getIrisOnlyUpdateAuthorized(void);

    static void setIrisOnlyUpdateAuthorized(bool authorized);

    /**
     * @brief Updates firmware and parameter from the given .D5FC file
     *
     * @param containerFilename Filename of the .D5FC file containing the
     *        firmware and parameter
     * @param sensorList List of sensors to update
     * @param resultMap Map receiving the update result for every sensor
     * @param checkSensorConsistency Check consistency from group sensors
     *        <code>true</code> = all sensors of a group must be included in
     *        the List and present, <code>false</code> = no check
     *        It is strongly recommended to set this parameter to true.
     *        Only set to false if you know what you are doing.
     * @param userData User-defined additional parameter
     * @param containerUpdateCallback Callback function for progress updates
     *
     * @return Operation result
     *         <code>true</code> = Update for all sensors passed,
     *         <code>false</code> = Update for at least one sensor failed
     */
    static bool performContainerUpdateForSensors(const std::string& containerFilename, Dist500List& sensorList ,
            UpdateResultMap& resultMap, bool checkSensorConsistency = true,
            void* userData = 0, CONTAINER_UPDATE_CALLBACK containerUpdateCallback = 0);

    /**
     * @brief Checks if the given firmware matches the hardware.
     *
     * @param hexFile Path to the firmware hex file.
     * @param userData User-defined additional parameter
     *
     * @return Result of the query if the firmware matches the hardware.
     */
    FirmwareFitHardwareResult firmwareFitsHardware(const std::string& hexFile,
        void* userData = 0);

    /**
     * @brief Checks if the given firmware matches the hardware.
     *
     * @param hexFile Path to the firmware hex file.
     * @param remainingGroupSensors List of slave sensors
     * @param resultMap Map receiving the check result for every sensor
     * @param userData User-defined additional parameter
     *
     * @return Operation result
     *         <code>true</code> = Check for all sensors passed,
     *         <code>false</code> = Check for at least one sensor failed
     */
    bool firmwareFitsHardware(const std::string& hexFile,
        Dist500List& remainingGroupSensors, FirmwareFitHardwareResultMap& resultMap,
        void* userData = 0);

    /**
     * @brief Checks if the given firmware matches the hardware.
     *
     * @param hexFile Path to the firmware hex file.
     * @param sensorList List of sensors
     * @param resultMap Map receiving the check result for every sensor
     * @param userData User-defined additional parameter
     *
     * @return Operation result
     *         <code>true</code> = Check for all sensors passed,
     *         <code>false</code> = Check for at least one sensor failed
     */
    static bool firmwareFitsHardwareForSensors(const std::string& hexFile,
        Dist500List& sensorList, FirmwareFitHardwareResultMap& resultMap,
        void* userData = 0);


    /**
     * Constructor
     *
     * @param sensor
     */
    FirmwareController(iris::drivers::Sensor& sensor);

    /**
     * Destructor
     */
    virtual ~FirmwareController();

    /**
     * Updates the application firmware part from the given .LDR file
     *
     * @param hexfileName Filename of the .LDR file containing the firmware
     * @param userData User-defined additional parameter for callback
     * @param updateCallback Callback function for progress updates
     *
     * @return Operation result
     */
    virtual SENSOR_RESULT performApplicationFirmwareUpdate(
            const std::string& hexfileName, void* userData,
            UPDATE_CALLBACK updateCallback);

    virtual SENSOR_RESULT performApplicationFirmwareUpdate(
            char* hexfileContents, unsigned long hexfileSize,
            const std::string& hexfileName, const std::string& firmwareTimestamp,
            void* userData, UPDATE_CALLBACK updateCallback);
    /**
     * Updates the application firmware info block according to the given .LDR file
     *
     * @param hexfileName Filename of the .LDR file containing the firmware
     * @param userData User-defined additional parameter for callback
     * @param updateCallback Callback function for progress updates
     *
     * @return Operation result
     */
    virtual SENSOR_RESULT writeApplicationFirmwareInfoBlock(
            const std::string& hexfileName, void* userData,
            UPDATE_CALLBACK updateCallback);

    /**
     * Updates the bootloader firmware part from the given .LDR file
     *
     * @param hexfileName Filename of the .LDR file containing the firmware
     * @param userData User-defined additional parameter for callback
     * @param updateCallback Callback function for progress updates
     *
     * @return Operation result
     */
    virtual SENSOR_RESULT performBootloaderFirmwareUpdate(
            const std::string& hexfileName, void* userData,
            UPDATE_CALLBACK updateCallback);

    virtual SENSOR_RESULT performBootloaderFirmwareUpdate(
            char* hexfileContents, unsigned long hexfileSize,
            const std::string& hexfileName, const std::string& firmwareTimestamp,
            void* userData, UPDATE_CALLBACK updateCallback);

    /**
     * Updates the bootloader firmware info block according to the given .LDR file
     *
     * @param hexfileName Filename of the .LDR file containing the firmware
     * @param userData User-defined additional parameter for callback
     * @param updateCallback Callback function for progress updates
     *
     * @return Operation result
     */
    virtual SENSOR_RESULT writeBootloaderFirmwareInfoBlock(
            const std::string& hexfileName, void* userData,
            UPDATE_CALLBACK updateCallback);

    /**
     * Loads the primary or secondary FPGA bitfile (firmware)
     *
     * @param bitfileName Filename of the .BIT file containing the firmware
     * @param primary <code>true</code> if primary image is to be loaded,
     *        <code>false</code> for secondary image
     * @param userData User-defined additional parameter for callback
     * @param updateCallback Callback function for progress updates
     *
     * @return Operation result
     */
    virtual SENSOR_RESULT loadFpgaImage(const std::string& bitfileName, bool primary,
            void* userData, UPDATE_CALLBACK updateCallback);

    virtual SENSOR_RESULT loadFpgaImage(const unsigned char* fileContents, unsigned int fileSize, bool primary,
            void* userData, UPDATE_CALLBACK updateCallback);

    virtual SENSOR_RESULT performFpgaImageVerification(const std::string& bitfileName, bool primary,
                                                       void* userData, UPDATE_CALLBACK updateCallback);

    virtual SENSOR_RESULT performFpgaImageVerification(const unsigned char* fileContents, unsigned int fileSize, bool primary,
                                                       void* userData, UPDATE_CALLBACK updateCallback);

    /**
     * Type for a MAC address (6 octets)
     */
    typedef unsigned char MacAddress[6];

    static const unsigned long FlashStartAddress = 0x20000000;

    static const unsigned long FlashSectorSize = 0x20000;

    static const unsigned long FlashBankSize = 0x200000;

    static const unsigned long ConfigurationDataFlashAddress = FlashStartAddress + 0x100000;

    // offset within flash, not absolute address in cpu address space !
    static const unsigned long START_FIRMWARE_INFO_APPL;
    static const unsigned long START_FIRMWARE_INFO_BOOT;
    static const unsigned long FIRMWARE_INFO_SIZE;
    static const unsigned long FIRMWARE_INFO_WITH_CRC_SIZE;

    /**
     * Retrieves information about the sensor
     *
     * @param forceRefresh
     *
     * @return SensorInfo instance with relevant data
     */
    SensorInfo getSensorInfo(bool forceRefresh = false);

    /**
     * Clears the sensor information cache
     */
    void invalidateSensorInfo(void);

    /**
     * Checks whether a cached sensor info exists
     *
     * @return <code>true</code> if info is available in cache, <code>false</code> otherwise
     */
    bool hasSensorInfo(void) const;

    /**
     * Typedef for a list of FirmwareController instances
     */
    typedef std::list<FirmwareController*> FirmwareControllerList;

    class ConfigurationInterceptor {

    protected:

        virtual void reviewConfiguration(const unsigned char index, const unsigned char total, iris::configuration::Dist500Configuration& config) = 0;

        friend class FirmwareController;

    };

    /**
     * Configures a sensor as master and optionally one or more sensors as slaves to
     * this master;
     *
     * @param slaves (Possibly empty) list of slaves
     * @param ipAddr IP address of the master sensor
     * @param netMask Network mask of the master sensor
     * @param gwAddr Getway address of the master sensor
     * @param port UIP IP port address.
     *             This parameter currently has no effect. The port address is fixed.
     * @param sntp1Addr Preferred SNTP server address
     * @param sntp2Addr Alternative SNTP server address
     * @param interceptor Class to configure additional parameters of the group such as function area address.
     *
     * @return Operation result
     */
    virtual SENSOR_RESULT configureSensorGroup(const FirmwareControllerList& slaves, const iris::configuration::CommunicationGroup::IpAddress& ipAddr,
                                               const iris::configuration::CommunicationGroup::IpAddress& netMask, const iris::configuration::CommunicationGroup::IpAddress& gwAddr,
                                               const unsigned short port, const iris::configuration::CommunicationGroup::IpAddress& sntp1Addr,
                                               const iris::configuration::CommunicationGroup::IpAddress& sntp2Addr, ConfigurationInterceptor& interceptor);

    /**
     * @brief Configures one sensor as single sensor
     * @param ipAddr IP address of the master sensor
     * @param netMask Network mask of the master sensor
     * @param gwAddr Getway address of the master sensor
     * @param port UIP IP port address.
     *             This parameter currently has no effect. The port address is fixed.
     * @param sntp1Addr Preferred SNTP server address
     * @param sntp2Addr Alternative SNTP server address
     * @param interceptor Class to configure additional parameters such as function area address.
     * @return
     */
    virtual SENSOR_RESULT configureStandalone(const iris::configuration::CommunicationGroup::IpAddress& ipAddr,
                                              const iris::configuration::CommunicationGroup::IpAddress& netMask, const iris::configuration::CommunicationGroup::IpAddress& gwAddr,
                                              const unsigned short port, const iris::configuration::CommunicationGroup::IpAddress& sntp1Addr,
                                              const iris::configuration::CommunicationGroup::IpAddress& sntp2Addr, ConfigurationInterceptor& interceptor);

    /**
     * Returns the SensorGroup instance
     *
     * @return Associated SensorGroup
     */
    SensorGroup* getSensorGroup(void);

    /**
     * Sets the associated SensorGroip
     *
     * @param sg SensorGroup instance
     */
    void setSensorGroup(SensorGroup* sg);

    /**
     * Returns the group index
     *
     * @return Sensor index within group
     */
    unsigned short getGroupIndex(void);

    /**
     * Sets the sensor index within a group
     *
     * @param gi Sensor index within group
     */
    void setGroupIndex(unsigned short gi);

    virtual SENSOR_RESULT performBootloaderFirmwareVerification(
            const std::string& hexfileName, void* userData,
            UPDATE_CALLBACK verificationCallback);

    virtual SENSOR_RESULT performBootloaderFirmwareVerification(
            char* hexfileContents, unsigned long hexfileSize,
            void* userData, UPDATE_CALLBACK updateCallback);

    virtual SENSOR_RESULT performApplicationFirmwareVerification(
            const std::string& hexfileName, void* userData,
            UPDATE_CALLBACK verificationCallback);

    virtual SENSOR_RESULT performApplicationFirmwareVerification(
            char* hexfileContents, unsigned long hexfileSize,
            void* userData, UPDATE_CALLBACK updateCallback);

protected:

    /**
     * May hold a SensorInfo instance for caching (0 if unused)
     */
    SensorInfo* sensorInfo;

    /**
     * Refres to the SensorGtroup, if any
     */
    SensorGroup* sensorGroup;

    /**
     * Contraing the sensor index within the group
     */
    unsigned short groupIndex;

    /**
     * Typedef for container update data
     */
    typedef struct{
        /**
         * User-defined additional parameter
         */
        void* userData;

        /**
         * Callback function for progress updates
         */
        CONTAINER_UPDATE_CALLBACK containerUpdateCallback;

        /**
         * Sensor instance
         */
        iris::dist500::Dist500* sensor;

        /**
         * Container update state
         */
        CONTAINER_UPDATE_STATE updateState;

        /**
         * Current container step
         */
        unsigned int containerStep;

        /**
         * Total number of container steps
         */
        unsigned int containerTotalSteps;

        /**
         * Number of firmware update steps
         */
        unsigned int firmwareUpdateSteps;

        /**
         * Flag to signal if the configuration is available for update
         */
        bool configurationAvailable;

        /**
         * Flag to signal to write the default values
         */
        bool defaultValues;

    } ContainerUpdateUserData;

    static bool irisOnlyUpdateAuthorized;

    /**
     * @brief Callback function for configuration parameter update
     *
     * @param userData User-defined additional parameter
     * @param index Index of current paramter
     * @param total Total parameters
     * @param groupId Parameter group id
     * @param paramId Parameter id
     */
    static void configurationContainerCallback(void* userData,
            iris::uip::ulong index, iris::uip::ulong total,
            iris::uip::ushort groupId, iris::uip::ushort paramId);

    /**
     * @brief Callback function container update
     *
     * @param userData User-defined additional parameter
     * @param step Current step
     * @param totalSteps Total number of steps
     * @param stepPercentage Progress within current step
     * @param totalPercentage Total progress
     */
    static void updateContainerCallback(void* userData, unsigned int step,
            unsigned int totalSteps, double stepPercentage,
            double totalPercentage);

    /**
     * @brief getDefaultSensorSerialPrefix
     * @param prefixMap
     */
    static void getDefaultSensorSerialPrefix(std::map<uint8_t, uint32_t>& prefixMap);

    /**
     * @brief Performs the container firmware update from the given .D5FC file
     *
     * @param containerFilename Filename of the .D5FC file containing the
     *        firmware and parameter
     * @param sensorList List of sensors to be updated
     * @param resultMap Map receiving the update result for every sensor
     * @param defaultValues Default values Flag
     *        <code>true</code> = Before the parameter update, all parameters
     *        get their default value, <code>false</code> = no default values
     * @param userData User-defined additional parameter
     * @param containerUpdateCallback Callback function for progress updates
     * @return Operation result
     *         <code>true</code> = Update for all sensors passed,
     *         <code>false</code> = Update for at least one sensor failed
     */
    static bool performContainerFirmwareUpdate(
            const std::string& containerFilename, Dist500List& sensorList,
            UpdateResultMap& resultMap, bool checkSensorConsistency,
            bool defaultValues, void* userData,
            CONTAINER_UPDATE_CALLBACK containerUpdateCallback);

    /**
     * @brief Check if all sensors of a group exist
     *
     * @param sensorList List of sensors to check
     * @param resultMap Map receiving the update result for every sensor
     *
     * @return Operation result <code>true</code> = all sensors are consistent,
     *         <code>false</code> = at least one group inconsistent
     */
    static bool checkSensorsConsistency(Dist500List& sensorList,
            UpdateResultMap& resultMap);

    /**
     * @brief Performs a application firmware update from container file.
     *
     * @param d5 Sensor instance
     * @param file Application firmware file
     * @param skipped Flag for skipped firmware <code>true</code> = firmware
     *        was skipped, <code>false</code> = otherwise
     * @param userData User-defined additional parameter
     *
     * @return Operation result <code>true</code> = update succesful,
     *         <code>false</code> = update failed
     */
    static bool updateContainerApplication(Dist500& d5,
            struct iris::legacy::_EMBEDDED_FILE& file, bool& skipped,
            void* userData);

    /**
     * @brief Performs a application firmware verifcation from container file.
     *
     * @param d5 Sensor instance
     * @param file Application firmware file
     * @param userData User-defined additional parameter
     * @return Operation result <code>true</code> = verify succesful,
     *         <code>false</code> = verify failed
     */
    static bool verifyContainerApplication(Dist500& d5,
            struct iris::legacy::_EMBEDDED_FILE& file, void* userData);

    /**
     * @brief Performs a communication firmware update from container file.
     *
     * @param d5 Sensor instance
     * @param file Communication firmware file
     * @param skipped Flag for skipped firmware <code>true</code> = firmware
     *        was skipped, <code>false</code> = otherwise
     * @param userData User-defined additional parameter
     * @return Operation result <code>true</code> = verify succesful,
     *         <code>false</code> = verify failed
     */
    static bool updateContainerCommunication(Dist500& d5,
            struct iris::legacy::_EMBEDDED_FILE& file, bool& skipped,
            void* userData);

    /**
     * @brief Performs a communication firmware verifcation from
     *        container file.
     *
     * @param d5 Sensor instance
     * @param file Communication firmware file
     * @param userData User-defined additional parameter
     * @return Operation result <code>true</code> = verify succesful,
     *         <code>false</code> = verify failed
     */
    static bool verifyContainerCommunication(Dist500& d5,
            struct iris::legacy::_EMBEDDED_FILE& file, void* userData);

    /**
     * @brief Performs a FPGA firmware update from container file.
     *
     * @param d5 Sensor instance
     * @param file FPGA firmware file
     * @param primary FPGA firmware position <code>true</code> = first FPGA
     *        firmware, <code>false</code> = second FPGA firmware
     * @param skipped Flag for skipped firmware <code>true</code> = firmware
     *        was skipped, <code>false</code> = otherwise
     * @param userData User-defined additional parameter
     * @return Operation result <code>true</code> = verify succesful,
     *         <code>false</code> = verify failed
     */
    static bool updateContainerFpga(Dist500& d5,
            struct iris::legacy::_EMBEDDED_FILE& file, bool primary,
            bool skipFpgaRelease, bool& skipped, void* userData);

    /**
     * @brief Performs a FPGA firmware verifcation from container file.
     *
     * @param d5 Sensor instance
     * @param file FPGA firmware file
     * @param primary FPGA firmware position <code>true</code> = first FPGA
     *        firmware, <code>false</code> = second FPGA firmware
     * @param userData User-defined additional parameter
     * @return Operation result <code>true</code> = verify succesful,
     *         <code>false</code> = verify failed
     */
    static bool verifyContainerFpga(Dist500& d5,
            struct iris::legacy::_EMBEDDED_FILE& file, bool primary, bool skipFpgaRelease,
            void* userData);

    /**
     * @brief Performs configuration parameter update from container file.
     *
     * @param sensor Sensor reference
     * @param decoder Firmware container decoder reference
     * @param config Reference to sensor configuration data
     * @param mismatches Reference to sensor configuration mismatches
     * @param defaultValues Default values Flag
     *        <code>true</code> = Before the parameter update, all parameters
     *        get their default value, <code>false</code> = no default values
     * @param resultMap Map receiving the update result for every sensor
     * @param userData User-defined additional parameter
     * @return Operation result <code>true</code> = verify succesful,
     *         <code>false</code> = verify failed
     */
    static bool performContainerParameterUpdate(Dist500& sensor,
            iris::legacy::Dist500FirmwareContainerDecoder& decoder,
            iris::configuration::Dist500Configuration& config,
            iris::dist500::Dist500Base::ConfigurationMismatches& mismatches,
            bool defaultValues, UpdateResultMap& resultMap, void* userData);

    /**
     * @brief Checks is a firmware info watermark in the give firmware
     *
     * @param hasWatermark Reference to the result of the check.
     * @param infoStart Address pointer to the start of the founded firmware release info block
     *
     * @return Operation result
     */
    static SENSOR_RESULT findFirmwareInfoWatermark(bool& hasWatermark, char *&infoStart);

    /**
     * @brief Performs the check for one sensor
     * @param hexReader Reference of HexFileStreamReader
     * @param hexfileName Firmware filename
     * @param sensor Sensor instance
     * @param fitResult Check result
     * @param userData User-defined additional parameter
     *
     * @return Operation result
     *         <code>true</code> = Check passed,
     *         <code>false</code> = Check failed
     */
    static bool firmwareFitsHardwareCheck(
            iris::hexfiles::HexFileStreamReader& hexReader, const std::string& hexfileName,
            Dist500* sensor, FirmwareFitHardwareResult& fitResult, void* userData);

    /**
     * @brief Performs the checks if the given firmware matches the hardware.
     *
     * @param hexFile Path to the firmware hex file.
     * @param sensorList List of sensors
     * @param resultMap Map receiving the check result for every sensor
     * @param userData User-defined additional parameter
     *
     * @return Operation result
     *         <code>true</code> = Check for all sensors passed,
     *         <code>false</code> = Check for at least one sensor failed
     */
    static bool performFirmwareFitsHardwareCheck(
            const std::string& hexFile, Dist500List& sensorList,
            FirmwareFitHardwareResultMap& resultMap, void* userData);
    
    /**
     * @brief waitForSensors Waits for sensors and invokes callback for progress bar update
     *
     * @param sensors List of sensors
     * @param timeMs Time in milliseconds
     * @param intervals Number of intervals between callback invocations
     */
    static void waitForSensors(Dist500List& sensors, ContainerUpdateUserData& containerUpdateUserData, unsigned int timeMs, unsigned int intervals);

}; // class FirmwareController

} // namespace dist500

} // namespace iris

#endif // DIST500_FIRMWARECONTROLLER_H
