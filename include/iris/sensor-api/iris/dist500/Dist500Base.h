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

#ifndef DIST500_DIST500BASE_H
#define DIST500_DIST500BASE_H

// STL includes
#include <map>
#include <set>
#include <bitset>

// iris includes
#include "iris/Common.h"
#include "iris/drivers/Sensor.h"
#include "iris/threads/Thread.h"
#include "iris/configuration/Configuration.h"
#include "iris/synchronization/Mutex.h"
#include "WorkingModeStatusSource.h"

namespace iris {

// forward declaration (used with friend statement)
namespace uff {
    class UffDecoder;
}

namespace dist500 {
    // forward declaration
    class Dist500;

// port numbers for UIP-over-UDP communication
const unsigned int STACK_LEVEL_PORT = 0x8888;
const unsigned int SERVICE_LEVEL_PORT = 0x8889;
const unsigned int APPL_LEVEL_PORT = 0x888a;

// default timeouts in ms
const unsigned int MAX_SCAN_IO_WAIT = 500;
const unsigned int MAX_SEND_IO_WAIT = 500;
const unsigned int MAX_DEFAULT_IO_WAIT = 1000;
const unsigned int MAX_PICTURE_IO_WAIT = 2000;
const unsigned int MAX_UPLOAD_IO_WAIT = 900000;
const unsigned int MAX_FLASH_ERASE_IO_WAIT = 35000;// Rel.1: 1300ms x 24 sectors = 31.2s; enough time to erase 1.5 banks for a firmware file.
const unsigned int MAX_FLASH_WRITE_IO_WAIT = 1000;
const unsigned int MAX_FPGA_RESET_IO_WAIT = 1000;
const unsigned int MAX_FINALIZE_WAIT = 20000;// For a group of 3 sensors this will take ~15s.

/**
 * Sensor operation result codes
 */
typedef enum {

    /**
     * Everything OK
     */
    OPERATION_PASSED = 0,

    /**
     * Generail failure
     */
    OPERATION_FAILED,

    /**
     * Unexpected UIP reply
     */
    OPERATION_WRONG_REPLY,

    /**
     * No UIP reply
     */
    OPERATION_NO_REPLY,

    /**
     * Incomplete UIP reply
     */
    OPERATION_INCOMPLETE_REPLY,

    /**
     * Unexpected subsequent UIP reply
     */
    OPERATION_WRONG_SUBSEQUENT_REPLY,

    /**
     * Erroneous subsequent UIP reply
     */
    OPERATION_ERRONEOUS_SUBSEQUENT_REPLY,

    /**
     * Function/method is reserved for iris-internal use
     */
    OPERATION_RESERVED_FOR_IRIS,

    OPERATION_INCONSISTENT_RESPONSE_PAYLOAD

} SENSOR_RESULT;

typedef std::list<Dist500*> Dist500List;

/**
 * Implements basic sensor functions like communication, configuration and UIP retry and timeout control.
 * Key methods are listed in "See also".
 * @see setWorkingMode
 * @see getConfigurationParameter
 * @see readConfiguration
 * @see listAllSupportedMessages
 * @see setUipTimeout
 * @see doSendAndGetReply
 */
class SENSORAPI Dist500Base {

protected:

    /**
     * UIP address of sensor
     */
    unsigned char uipAddress;

    /**
     * Reference to associatee driver's Sensor object
     */
    iris::drivers::Sensor& sensor;

    /**
     * Implements a dispatcher which maps spontaneous UIP frames (sub-command *) to
     * message handler methods
     */
    class SpontaneousHandlers {

    public:

        /**
         * Typedef for a callback method
         *
         * @param base Dist500Base instance which provides the handler
         * @param message UIP spontaneous message instance
         */
        typedef void (*UIP_MESSAGE_HANDLER) (Dist500Base* base, UipMessage* message);

        /**
         * Computes a type and version (8-bit each) into one 16-bit integer
         */
        static unsigned short makeTypeAndVersion(unsigned char type, unsigned char version);

        /**
         * Typedef for a map from type-version combinations to handlers
         */
        typedef std::map<unsigned short, UIP_MESSAGE_HANDLER> UipHandlerMap;

        /**
         * Mutex
         */
        iris::synchronization::Mutex mutex;

        /**
         * Holds the handler map
         */
        UipHandlerMap uipHandlerMap;

        /**
         * Registers a handler for a spontaneous message type
         *
         * @param type UIP type tag
         * @param version UIP version tag
         * @param handler Message handler to be called
         */
        void registerHandler(unsigned char type, unsigned char version, UIP_MESSAGE_HANDLER handler);

        /**
         * Forwards a message to the registered handler (if any)
         *
         * @param message Spontaeous UIP message instance
         */
        void forward(UipMessage* message);

        /**
         * Links to the owning Dist500Base instance
         */
        Dist500Base* base;

        /**
         * Constructor
         *
         * @param base Owning Dist500Base instance
         */
        SpontaneousHandlers(Dist500Base* base);

    };

    /**
     * Handler manger for spontaeous UIP messages (sub-command *)
     */
    SpontaneousHandlers handlers;

    typedef std::set<int> NoRetryMessageHashSet;

    NoRetryMessageHashSet noRetryMessageHashSet;

    /**
     * Checks if automatic retries are currently supported for the specified message.
     * They can be disabled via registerNoRetryMessage which is checked by this method.
     * The global disabling via disableAutomaticRetries overrides that and is not checked with this method.
     * @param message
     * @return
     * @see registerNoRetryMessage
     * @see disableAutomaticRetries
     */
    bool automaticRetriesSupported(UipMessage* message);

    /**
     * Makes the specified message not be automatically resent if no replay arrives.
     * Is called for some messages in initializeNoRetryMessageHashSet().
     * @param type
     * @param version
     * @param command
     * @see automaticRetriesSupported
     * @see enableAutomaticRetries
     * @see disableAutomaticRetries
     * @see setUipTimeout
     */
    void registerNoRetryMessage(unsigned char type, unsigned char version, unsigned char command);

    /**
     * These are the messages that are not automatically repeated in case no reply arrives.
     * Reasons are given in source code after each call to registerNoRetryMessage.
     * Typical reasons are when a message has side-effects and can not be retried without knowledge of the user.
     * @see registerNoRetryMessage
     */
    void initializeNoRetryMessageHashSet(void);

    static bool automaticRetriesDisabled;

    /**
     * Timeout in ms used for UIP send and get reply methods
     */
    int uipTimeout;

public:

    /**
     * Constructor
     *
     * @param sensor Associated Sensor instance (from Driver)
     */
    Dist500Base(iris::drivers::Sensor& sensor);

    /**
     * Destructor
     */
    virtual ~Dist500Base() {}

    /**
     * Sends an application level message and receives one or more replies
     *
     * @param message Message to be sent
     * @param timeoutMs Receive timeout in milliseconds
     * @param replyCount Number of expected reply messages
     * @param failOnLessReplies When set, then less than replyCount replies mean failure
     *
     * @return Received message (may be linked with others) or 0 if no
     *         reply has occured
     */
    UipMessage* sendAndGetApplReply(UipMessage *message, int timeoutMs =
            MAX_DEFAULT_IO_WAIT, int replyCount = 1, bool failOnLessReplies = true);

    /**
     * Sends a stack level message and receives one or more replies
     *
     * @param message Message to be sent
     * @param timeoutMs Receive timeout in milliseconds
     * @param replyCount Number of expected reply messages
     * @param failOnLessReplies When set, then less than replyCount replies mean failure
     *
     * @return Received message (may be linked with others) or 0 if no
     *         reply has occured
     */
    UipMessage* sendAndGetStackReply(UipMessage *message, int timeoutMs =
            MAX_DEFAULT_IO_WAIT, int replyCount = 1, bool failOnLessReplies = true);

    /**
     * Sends an application level message and receives one or more replies
     *
     * @param message Message to be sent
     * @param timeoutMs Receive timeout in milliseconds
     * @param replyCount Number of expected reply messages
     * @param failOnLessReplies When set, then less than replyCount replies mean failure
     *
     * @return Received message (may be linked with others) or 0 if no
     *         reply has occured
     * @see doSendAndGetReply
     */
    UipMessage* doSendAndGetApplReply(UipMessage *message, int timeoutMs, int replyCount, bool failOnLessReplies = true);

    /**
     * Sends a service level message and receives one or more replies
     * @param message
     * @param timeoutMs
     * @param replyCount
     * @param failOnLessReplies When set, then less than replyCount replies mean failure
     * @return
     * @see doSendAndGetReply
     */
    UipMessage* doSendAndGetServiceReply(UipMessage *message, int timeoutMs, int replyCount, bool failOnLessReplies = true);

    UipMessage* sendAndGetServiceReply(UipMessage *message, int timeoutMs =
            MAX_DEFAULT_IO_WAIT, int replyCount = 1, bool failOnLessReplies = true);

    /**
     * Sends a stack level message and receives one or more replies
     *
     * @param message Message to be sent
     * @param timeoutMs Receive timeout in milliseconds
     * @param replyCount Number of expected reply messages
     * @param failOnLessReplies If set, then less than replyCount replies mean failure
     *
     * @return Received message (may be linked with others) or 0 if no
     *         reply has occured
     * @see doSendAndGetReply
     */
    UipMessage* doSendAndGetStackReply(UipMessage *message, int timeoutMs, int replyCount, bool failOnLessReplies = true);

    /**
     * Sends a stack or application level message and receives one or more replies
     *
     * @param level UIP message level. from highest to lowest: application, service or stack.
     * @param message Message to be sent
     * @param timeoutMs Receive timeout in milliseconds
     * @param replyCount Number of expected reply messages
     * @param failOnLessReplies If set, then less than replyCount replies mean failure
     *
     * @return Received message (may be linked with others) or 0 if no
     *         reply has occured
     * @see doSendAndGetApplReply
     * @see doSendAndGetServiceReply
     * @see doSendAndGetStackReply
     * @see sendUipCommand
     */
    UipMessage* doSendAndGetReply(int level, UipMessage *message, int timeoutMs, int replyCount, bool failOnLessReplies = true);

    /**
     * Retrieves a device feature
     *
     * @param group Feature group
     * @param param Feature id
     * @param buffer Buffer to receive feature value
     *
     * @return Operation result
     * @deprecated This functionality is now provided by UipGetFirmwareFeaturesRequest
     */
    SENSOR_RESULT _legacyGetDeviceInfo(unsigned short group, unsigned short param, char* buffer);

    /**
     * Reads a configuration parameter
     *
     * @param group Parameter group
     * @param param Parameter id
     * @param buffer Buffer to receive feature value
     * @param len Buffer receiving the actual length in bytes
     *
     * @return Operation result
     * @see setConfigurationParameter
     */
    SENSOR_RESULT getConfigurationParameter(unsigned short group, unsigned short param,
                                char* buffer, unsigned short& len, bool stackLevel = false);

    /**
     * Reads a configuration parameter from RAM of the sensor (not from flash).
     *
     * @param group Parameter group
     * @param param Parameter id
     * @param buffer Buffer to receive feature value
     *
     * @return Operation result
     * @see setConfigurationParameter
     * @see setConfigurationParameterIfKnown
     */
    SENSOR_RESULT getConfigurationParameter(unsigned short group, unsigned short param,
                                char* buffer, bool stackLevel = false);

    /**
     * @brief Sets a configuration parameter in the sensor's RAM (not in the flash).
     * @see getConfigurationParameter
     * @see setConfigurationParameterIfKnown
     */
    SENSOR_RESULT setConfigurationParameter(unsigned short group, unsigned short param,
                                const char* buffer, unsigned short len, bool stackLevel = false);
    /**
     * @brief Like setConfigurationParameter but only if that parameter is known.
     * @see setConfigurationParameter
     * @see getConfigurationParameter
     */
    SENSOR_RESULT setConfigurationParameterIfKnown(unsigned short group, unsigned short param,
                                const char* buffer, unsigned short len, bool& paramWasUnknown, bool stackLevel = false);

    /**
     * Returns a description for the sensor (ConnectionName + @ + UipAddress)
     *
     * @param buffer Buffer to receive name
     * @param maxLen Buffer capacity
     * @see getConnectionName
     * @see getLocalConnectionName
     */
    virtual void getName(char* nameBuffer, int maxLen);

    /**
     * Returns a description for the connection
     *
     * @param buffer Buffer to receive name
     * @param maxLen Buffer capacity
     * @see getName
     * @see getLocalConnectionName
     */
    virtual void getConnectionName(char* buffer);

    /**
     * Captures the sensor: Marks the device as captured, which can be queried by getCaptureState.
     * The sensor will keep functioning normally and its working mode is not changed.
     *
     * @param application Application display name
     * @return Operation result
     * @see releaseDevice
     * @see getCaptureState
     * @see setWorkingMode
     */
    SENSOR_RESULT captureDevice(char* application);

    /**
     * Releases ("uncaptures") the sensor. Has no effect on the working mode.
     *
     * @return Operation result
     * @see captureDevice
     * @see getCaptureState
     */
    SENSOR_RESULT releaseDevice(void);

    /**
     * Returns the capture state
     *
     * @param applicationBuffer Buffer to receive the capturing app's name
     * @param maxLen Buffer capacity
     * @return Operation result
     * @see captureDevice
     * @see releaseDevice
     */
    SENSOR_RESULT getCaptureState(char* applicationBuffer, int maxLen);

    /**
     * Returns the UIP address (integer between 1-255). The UIP address is the number after the hash sign in a URL.
     * @see setUipAddress
     * @see getConnectionName
     * @see getLocalConnectionName
     * @see getName
     */
    unsigned char getUipAddress(void);

    /**
     * @brief setUipAddress Sets a new UIP address for communication with this sensor. The UIP address is the number after the hash sign in a URL.
     * @note If the UIP changes, it must be updated, otherwise messages will not be received (discarded) or sent to a wrong address.
     * @note The UIP address can change on grouping or ungrouping of sensors. Direct configuration of the UIP is another possibility.
     * @see getUipAddress
     * @see getConnectionName
     * @see getLocalConnectionName
     * @see getName
     */
    void setUipAddress(unsigned char);

    /**
     * Performs an echo test (pings the sensor)
     *
     * @param payload Pointer to payload bytes
     * @param payloadLen Number of payload bytes to be used
     * @param Communication timeout in ms
     *
     * @return Operation result
     * @see pingSensor
     *
     * @deprecated This method only exists for backwards compatibility. Please
     *          use pingSensor() instead.
     */
    SENSOR_RESULT echoTest(const char* const payload,
            const unsigned short payloadLen, int timeoutMs = MAX_DEFAULT_IO_WAIT);

    /**
     * Pings a sensor. No repetitions if there is no reply, so the roundtrip time may be measured and compared.
     *
     * @param payload Pointer to payload bytes
     * @param payloadLen Number of payload bytes to be used
     * @param Communication timeout in ms
     *
     * @return Operation result
     * @see pingNeighbour
     */
    SENSOR_RESULT pingSensor(const char* const payload,
            const unsigned short payloadLen, int timeoutMs = MAX_DEFAULT_IO_WAIT);

    /**
     * Asks a sensor to ping one of its neighbours (same FA) for
     * a given number of repetitions
     *
     * @param neighbourAddress UIP address of neighbour
     * @param payloadLen Payload size of ping message
     * @param repetitions Number of ping repetitions
     * @param timeoutMs Communication timeout in milliseconds (between sensors)
     * @param successCount Returns the number of successful pings
     * @param averageTimeMs Average communication time per ping
     *
     * @return Operation result
     * @see pingSensor
     */
    SENSOR_RESULT pingNeighbour(const unsigned char neighbourAddress,
        const unsigned short payloadLen, const unsigned short repetitions,
        const unsigned short timeoutMs, unsigned short& successCount,
        unsigned short& averageTimeMs);

    /**
     * Returns an identifier string for local connection (eg IP:port); Currently returns a fixed dummy string.
     */
    virtual void getLocalConnectionName(char* buffer);

    /**
     * Sends a "free" UIP command to the sensor and waits for the reply.
     * This is the lowest level method for sending messages.
     *
     * @see doSendAndGetReply
     */
    SENSOR_RESULT sendUipCommand(char type, unsigned char version, char command,
            unsigned short payloadLen, char* payload, unsigned int timeoutMs,
            char &replyType, unsigned char &replyVersion, char &replyCommand,
            unsigned short &replyPayloadLen, char* replyPayloadBuffer);

    typedef std::map<unsigned short, std::string> ParameterGroups;

    typedef std::set<unsigned short> IdSet;

    /**
     * Retrieves a map (ParameterGroups) of group ids to group name.
     * Convenience wrapper of getParameterGroupIds and getGroupName.
     * @param groups output parameter
     * @see
     */
    SENSOR_RESULT getParameterGroups(ParameterGroups& groups);

    /**
     * Retrieves a set of existing group ids. Continue sensor configuration readout via readAllGroupParameters.
     * @param groupIds output parameter
     * @see getGroupName
     * @see getConfigurationParameter
     * @see readAllGroupParameters
     */
    SENSOR_RESULT getParameterGroupIds(IdSet& groupIds);

    /**
     * @brief The ParameterInfo class holds parameter information like name and value range.
     * @see getParameterInfos
     * @see getParameterIds
     * @todo replace public members by protected ones plus accessor methods
     */
    class ParameterInfo {
    public:
        std::string name;
        iris::configuration::ParameterGroup::DataType dataType;
        unsigned short arraySize;
        unsigned short totalSize;
        signed long minValue;
        signed long maxValue;
        signed long defaultValue;
        char* arrayDefault;
        iris::configuration::ParameterGroup::UpdateType updateType;
        ParameterInfo();
        ~ParameterInfo();
        ParameterInfo(const ParameterInfo& source);
        ParameterInfo& operator = (ParameterInfo& source);
    };

    typedef std::map<unsigned short, ParameterInfo> ParameterInfos;

    SENSOR_RESULT getParameterInfos(const unsigned short groupId, ParameterInfos& infos, const bool includeNames = false);

    SENSOR_RESULT getParameterIds(const unsigned short groupId, IdSet& paramIds);

    /**
     * @brief The TemporaryConfiguration class
     */
    class SENSORAPI TemporaryConfiguration: public iris::configuration::Configuration {

    public:

        TemporaryConfiguration();

        void clear(void);

        iris::configuration::ParameterGroup* addGroup(const iris::uip::ushort id, const std::string& name);

    };

    /**
     * @brief The ConfigurationMismatches class
     */
    class SENSORAPI ConfigurationMismatches {

    protected:

        TemporaryConfiguration unknownToSensor;

        TemporaryConfiguration unknownToPc;

        friend class Dist500Base;

        friend class iris::uff::UffDecoder;

    public:

        void clear(void);

        ConfigurationMismatches();

        ~ConfigurationMismatches();

        TemporaryConfiguration& getUnknownToSensor();

        TemporaryConfiguration& getUnknownToPc();

    };

    /**
     * Callback for sensor configuration transfers
     *
     * @param userData User-defined additional parameter for callback
     * @param index Current index of configuration parameter (0..total - 1)
     * @param total Total count of configuration parameters
     * @param groupId Current parameter group id
     * @param paramId Current parameter id
     * @see readConfiguration
     */
    typedef void (*TRANSFER_CONFIGURATION_CALLBACK) (void* userData, iris::uip::ulong index, iris::uip::ulong total, iris::uip::ushort groupId, iris::uip::ushort paramId);

    /**
     * Reads the sensor configuration RAM shadow
     *
     * @param config Reference to sensor configuration receiving the data
     * @param callback Callback for sensor configuration transfer
     * @param userData User-defined additional parameter for callback
     *
     * @return Operation result
     *
     * @see iris::dist500::Dist500Base::TRANSFER_CONFIGURATION_CALLBACK
     * @note Sensor configuration contains only parameters known both to sensor and PC.
     */
    SENSOR_RESULT readConfiguration(iris::configuration::Dist500Configuration& config, TRANSFER_CONFIGURATION_CALLBACK callback = 0, void* userData = 0);

    /**
     * Reads the sensor configuration RAM shadow
     *
     * @param config Reference to sensor configuration receiving the data
     * @param mismatches Reference to sensor configuration mismatches receiving the data
     * @param callback Callback for sensor configuration transfer
     * @param userData User-defined additional parameter for callback
     *
     * @return Operation result
     *
     * @note Sensor configuration contains only parameters known both to sensor and PC.
     *       Sensor configuration mismatches contain all other parameters
     */
    SENSOR_RESULT readConfiguration(iris::configuration::Dist500Configuration& config, ConfigurationMismatches& mismatches, TRANSFER_CONFIGURATION_CALLBACK callback = 0, void* userData = 0);

    // TODO implement readConfiguration() method for arbitrary Configuration instances, not only those of type *Dist500*Configuration

//#ifdef IRIS_INTERNAL_BUILD

    /**
     * Writes the sensor configuration RAM shadow
     *
     * @param config Reference to sensor configuration receiving the data
     * @param callback Callback for sensor configuration transfer
     * @param userData User-defined additional parameter for callback
     *
     * @return Operation result
     *
     * @note Sensor configuration contains only parameters known both to sensor and PC.
     */
    SENSOR_RESULT writeConfiguration(iris::configuration::Dist500Configuration& config, TRANSFER_CONFIGURATION_CALLBACK callback = 0, void* userData = 0);

    /**
     * Writes the sensor configuration RAM shadow
     *
     * @param config Reference to sensor configuration receiving the data
     * @param mismatches Reference to sensor configuration mismatches receiving the data
     * @param callback Callback for sensor configuration transfer
     * @param userData User-defined additional parameter for callback
     *
     * @return Operation result
     *
     * @note Sensor configuration contains only parameters known both to sensor and PC.
     *       Sensor configuration mismatches contain all other parameters
     */
    SENSOR_RESULT writeConfiguration(iris::configuration::Dist500Configuration& config, ConfigurationMismatches& mismatches, TRANSFER_CONFIGURATION_CALLBACK callback = 0, void* userData = 0);

    // TODO implement writeConfiguration() method for arbitrary Configuration instances, not only those of type *Dist500*Configuration
    //      in other words: add a public wrapper for _writeConfiguration() which already uses the base type in its interface

    /**
     * Copies the configuration from RAM to flash memory.
     * @see restoreConfigurationFromFlash
     * @see activateConfiguration
     */
    SENSOR_RESULT saveConfigurationToFlash(void);

//#endif

    /**
     * Copies the configuration from flash memory to RAM.
     * @see activateConfiguration
     * @see saveConfigurationToFlash
     */
    SENSOR_RESULT restoreConfigurationFromFlash(void);

    /**
     * @brief activates a configuration that is already in RAM
     * @see restoreConfigurationFromFlash
     * @see saveConfigurationToFlash
     */
    SENSOR_RESULT activateConfiguration(void);

    /**
     * @brief checkSupportForMessage Checks if the sensor can respond to the specified message.
     * @see listAllSupportedMessages
     */
    SENSOR_RESULT checkSupportForMessage(const unsigned char command, const unsigned char version, const unsigned char subCommand, bool& isSupported);

    typedef std::list<iris::uip::messageTypeDef> MessageTypeDefinitionList;

    /**
     * @brief listAllSupportedMessages lists all messages the sensor can respond to.
     * @see checkSupportForMessage
     */
    SENSOR_RESULT listAllSupportedMessages(MessageTypeDefinitionList& buffer);

//#ifdef IRIS_INTERNAL_BUILD

    /**
     * @brief lockImmanentData
     * @see unlockImmanentData
     */
    SENSOR_RESULT lockImmanentData(void);

    /**
     * @brief unlockImmanentData
     * @see lockImmanentData
     */
    SENSOR_RESULT unlockImmanentData(void);

//#endif

    /**
     * @brief describeParameter Returns ParameterInfo for the specified parameter which contains the type and value range.
     * @param groupId
     * @param paramId
     * @param info
     * @param includeName
     * @return
     * @see describeParameterWithoutName
     * @see getParameterName
     */
    SENSOR_RESULT describeParameter(const unsigned short groupId, const unsigned short paramId, ParameterInfo& info, const bool includeName = false);

    /**
     * @brief getParameterName Returns only the name of the specified parameter
     * @param groupId
     * @param paramId
     * @param paramName output parameter
     * @see describeParameter
     */
    SENSOR_RESULT getParameterName(const unsigned short groupId, const unsigned short paramId, std::string& paramName);

    /**
     * Sets the sensor working mode
     *
     * @param mode sensor working mode to be set
     * @see getWorkingMode
     */
    SENSOR_RESULT setWorkingMode(const iris::uip::working_mode mode);

    /**
     * Retrieves the sensor working mode (iris::uip::working_mode).
     *
     * @param mode Reference to sensor working mode variable receiving the data
     * @see setWorkingMode
     */
    SENSOR_RESULT getWorkingMode(iris::uip::working_mode& mode);

protected:

    /**
     * Callback function for spontaneous messages (sub-command *), here only for
     * U 2.0. If the sensor reports its working mode, it is dispatched via these.
     *
     * @param base Dist500Base instance (surrogate for this pointer)
     * @param message Spontaneously received message
     * @see getWorkingMode
     * @see setWorkingMode
     */
    static void handleSpontaneousWorkingModeMessage(Dist500Base* base, UipMessage* message);

    SENSOR_RESULT _writeConfiguration(iris::configuration::Configuration& config, ConfigurationMismatches& mismatches, TRANSFER_CONFIGURATION_CALLBACK callback = 0, void* userData = 0);

    /**
     * @brief The ParameterValue class
     */
    class ParameterValue {

    public:

        ParameterValue(const unsigned short len, const unsigned short definedLen, const void* value);

        ParameterValue();

        ~ParameterValue();

        unsigned short getLen(void) const;

        unsigned short getDefinedLen(void) const;

        void getValue(void* buffer) const;

    protected:

        unsigned short len;

        unsigned short definedLen;

        char value[256];

    };

    typedef std::map<unsigned short, ParameterValue> GroupParameterValues;

    typedef std::bitset<1024> ReceptionFlags;

    SENSOR_RESULT _readAllGroupParameters(const unsigned short groupId, GroupParameterValues& values, const bool truncateStrings, const bool sendEmptyIfDefault, ReceptionFlags& receivedParams, iris::uip::ushort& expectedCount);

    /**
     * Used for sensor configuration readout, returns a map with parameter values for the specified configuration group.
     * @param values output map of parameter id to parameter value
     * @see getGroupName
     * @see getParameterGroupIds
     * @see getParameterGroups
     * @see getConfigurationParameter
     */
    SENSOR_RESULT readAllGroupParameters(const unsigned short groupId, GroupParameterValues& values, const bool truncateStrings = true, const bool sendEmptyIfDefault = true);

    SENSOR_RESULT _optimizedReadConfiguration(iris::configuration::Dist500Configuration& config, ConfigurationMismatches& mismatches, TRANSFER_CONFIGURATION_CALLBACK callback = 0, void* userData = 0);

    SENSOR_RESULT _legacyReadConfiguration(iris::configuration::Dist500Configuration& config, ConfigurationMismatches& mismatches, TRANSFER_CONFIGURATION_CALLBACK callback = 0, void* userData = 0);

    /**
     * @brief describeParameterWithoutName Gets type and value range information for the specified parameter.
     * @see describeParameter
     * @see getParameterName
     * @see getConfigurationParameter
     */
    SENSOR_RESULT describeParameterWithoutName(const unsigned short groupId, const unsigned short paramId, ParameterInfo& info);

    typedef std::map<unsigned short, ParameterInfo> GroupParameterInfos;

    /**
     * @brief describeAllGroupParametersWithoutNames Gets descriptions (GroupParameterInfos) of parameters within the specified configuration group.
     * @see readAllGroupParameters
     */
    SENSOR_RESULT describeAllGroupParametersWithoutNames(const unsigned short groupId, GroupParameterInfos& infos);

    SENSOR_RESULT _describeAllGroupParametersWithoutNames(const unsigned short groupId, GroupParameterInfos& infos, ReceptionFlags& receivedParameters, iris::uip::ushort& expectedCount);

//#ifdef IRIS_INTERNAL_BUILD

    SENSOR_RESULT requestKeyPuzzle(unsigned short& puzzleLen, unsigned char* puzzleBuffer);

    /**
     * @brief unlockImmanentData
     * @see lockImmanentData
     */
    SENSOR_RESULT unlockImmanentData(const unsigned short keyLen, const unsigned char* key);

//#endif

    /**
     * @brief getGroupName Gets the name of the specified configuration group.
     * @param groupId
     * @param groupName
     * @return
     * @see readAllGroupParameters
     */
    SENSOR_RESULT getGroupName(const unsigned short groupId, std::string& groupName);

    SENSOR_RESULT _setConfigurationParameter(unsigned short group, unsigned short param, const char* buffer,
                                             unsigned short len, bool stackLevel, bool ignoreUnknownParamErrors, bool& paramWasUnknown);

    /**
     * Constant offset to be applied to standard timeouts
     */
    unsigned long timeoutOffset;

    /**
     * Factor to applied to standard timeouts
     */
    float timeoutFactor;

    /**
     * Returns the timeout offset
     *
     * @return Timeout offset
     */
    unsigned long getTimeoutOffset(void) const;

    /**
     * Returns the timeout factor
     *
     * @return Timeout factor
     */
    float getTimeoutFactor(void) const;

public:

    /**
     * Measures the timeout params (offset and factor) by doing
     * some comnmunication tests
     *
     * @return Operation result
     */
    SENSOR_RESULT determineTimeoutParameters(void);

    /**
     * Resets the timeout params to the default values (offset 0, factor 1.0)
     */
    void resetTimeoutParameters(void);

    friend class iris::drivers::Sensor;

    /**
     * Returns the associated Sensor instance (from Driver)
     */
    iris::drivers::Sensor& getSensor(void);

    /**
     * enables the automatic retries (except for messages where it was disabled via registerNoRetryMessage).
     * @see disableAutomaticRetries
     * @see setUipTimeout
     */
    static void enableAutomaticRetries(void);

    /**
     * disables the automatic retries (except for messages where it was disabled via registerNoRetryMessage).
     *
     * @see enableAutomaticRetries
     * @see setUipTimeout
     */
    static void disableAutomaticRetries(void);

    /**
     * Sets timeout used for UIP send and get reply methods (whereafter usually a retry is performed).
     * Can be useful on slow or crowded networks.
     * Some long operations like EraseFirmware use a different timeout value that is not affected.
     *
     * @param timeoutMs Timeout in milliseconds
     */
    void setUipTimeout(const int timeoutMs);

}; // class Dist500Base

} // namespace dist500

} // namespace iris

#endif // DIST500_DIST500BASE_H
