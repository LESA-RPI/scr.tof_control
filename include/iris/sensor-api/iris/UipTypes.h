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

// ###########################################################################
// ##                                                                       ##
// ##  W A R N I N G  *  W A R N I N G  *  W A R N I N G  *  W A R N I N G  ##
// ##                                                                       ##
// ##  THIS IS AUTOMATICALLY GENERATED CODE. DO NOT EDIT. ANY MODIFICATION  ##
// ##  WILL BE OVERWRITTEN BY THE OUTPUT OF THE NEXT CODE GENERATION RUN !  ##
// ##                                                                       ##
// ###########################################################################

#ifndef __UIPTYPES_H
#define __UIPTYPES_H

namespace iris {

namespace uip {

// Type definitions based on default C++ types

/**
 * 8 bit unsigned int
 */
typedef unsigned char uchar;

/**
 * 8 bit signed int
 */
typedef signed char schar;

/**
 * 16 bit unsigned int
 */
typedef unsigned short ushort;

/**
 * 16 bit signed int
 */
typedef signed short sshort;

/**
 * 32 bit unsigned int
 */
typedef unsigned long ulong;

/**
 * 32 bit signed int
 */
typedef signed long slong;

/**
 * 64 bit unsigned int
 */
typedef unsigned long long ulonglong;

/**
 * 64 bit signed int
 */
typedef signed long long slonglong;

// Aliases

/**
 * Alias for uchar
 */
typedef uchar ubyte;

/**
 * Alias for schar
 */
typedef schar sbyte;

// Specializations

/**
 * Sensor-internal picture number (starts at 1 after power-up or reset)
 */
typedef ulong pic_no;

/**
 * Sensor-internal timestamp (0.1 ms since 1970-01-01 00:00:00.000)
 */
typedef ulonglong timestamp;

/**
 * Count result
 */
typedef sshort count_result;

/**
 * Category ID
 */
typedef uchar category_id;

/**
 * Door state
 */
typedef uchar door_state;

// Enumerations

/**
 * Helper template for enums based on a specific base type
 * but with a specific size
 */
#pragma pack(1)
template <class E, class T> struct TypedEnum {
    typedef T TargetType;
    typedef E EnumType;
    TypedEnum(): _value(E()) { }
    TypedEnum(E value) { _value = static_cast<T>(value); }
    operator E() const { return static_cast<E>(_value); }
private:
    T _value;
};
#pragma pack()

/**
 * Simple boolean flag
 */
typedef enum {

    /**
     * Flag is set (true)
     */
    flag_set = 1,

    /**
     * Flag is unset (false)
     */
    flag_not_set = 0,

    __first_unused_bool_flag

} __bool_flag; // typedef enum __bool_flag

/**
 * Simple boolean flag
 * Consider as identical to __bool_flag
 */
#pragma pack(1)
typedef TypedEnum<__bool_flag, uchar> bool_flag; // typedef bool_flag
#pragma pack()
/**
 * Indicates the type of a sub-picture
 */
typedef enum {

    /**
     * Sub-picture contains amplitude values
     */
    amplitude = 'A',

    /**
     * Sub-picture contains distance values
     */
    distance = 'D',

    /**
     * Sub-picture contains both amplitude and distance values
     */
    both = 'B',

    __first_unused_sub_pic_type

} __sub_pic_type; // typedef enum __sub_pic_type

/**
 * Indicates the type of a sub-picture
 * Consider as identical to __sub_pic_type
 */
#pragma pack(1)
typedef TypedEnum<__sub_pic_type, uchar> sub_pic_type; // typedef sub_pic_type
#pragma pack()
/**
 * Indicates a transfer type during the installation mode
 */
typedef enum {

    /**
     * Distance and amplitude sub-pictures will be transmitted (7 bits plus saturation)
     */
    full_8 = 'f',

    /**
     * Only distance sub-pictures will be transmitted (7 bits plus saturation)
     */
    dist_only_8 = 'd',

    /**
     * Only amplitude sub-pictures will be transmitted (7 bits plus saturation)
     */
    ampl_only_8 = 'a',

    /**
     * Distance and amplitude sub-pictures will be transmitted (12 bits plus saturation)
     */
    full_16 = 'F',

    /**
     * Only distance sub-pictures will be transmitted (12 bits plus saturation)
     */
    dist_only_16 = 'D',

    /**
     * Only amplitude sub-pictures will be transmitted (12 bits plus saturation)
     */
    ampl_only_16 = 'A',

    __first_unused_inst_mode

} __inst_mode; // typedef enum __inst_mode

/**
 * Indicates a transfer type during the installation mode
 * Consider as identical to __inst_mode
 */
#pragma pack(1)
typedef TypedEnum<__inst_mode, uchar> inst_mode; // typedef inst_mode
#pragma pack()
/**
 * Indicates the type of sensor working mode
 */
typedef enum {

    /**
     * Sensor works in energy saving mode
     */
    energy_save_mode = 'E',

    /**
     * Sensor works in normal mode
     */
    normal_mode = 'N',

    /**
     * Sensor works in signal recording mode
     */
    signal_record_mode = 'R',

    /**
     * Mode to configure and update the Sensor
     */
    config_and_update_mode = 'C',

    /**
     * Mode to upload and simulate picture streams in realtime
     */
    realtime_upload_mode = 'U',

    /**
     * Mode to upload single pictures
     */
    single_picture_upload_mode = 'u',

    /**
     * Sensor works in activated mode
     */
    normal_activated_mode = 'A',

    __first_unused_working_mode

} __working_mode; // typedef enum __working_mode

/**
 * Indicates the type of sensor working mode
 * Consider as identical to __working_mode
 */
#pragma pack(1)
typedef TypedEnum<__working_mode, uchar> working_mode; // typedef working_mode
#pragma pack()
/**
 * Indicates the type of the counter
 */
typedef enum {

    /**
     * current counter
     * Incremented on each count event
     * Automatically added to buffer counter on count finish event following sensor deactivation and reset immediately afterwards
     */
    current_counter = 'C',

    /**
     * buffer counter
     * Used to store count result for a sensor activation period
     * There is no automatic reset of this counter as long as there is no sensor reset. Typically it is reset by command after query
     */
    buffer_counter = 'B',

    /**
     * single count event
     * Used on indication of count event
     * With respect to all count categories only one counter value is equal to 1 while all others are equal to 0
     * Intended for use during installation mode 
     */
    single_event = 'S',

    /**
     * start counter
     * Incremented on each count event
     * There is not automatic reset of this counter as long as there is no sensor reset and reset by command is not intended.
     * As a result this counter may overflow under usual operating conditions
     */
    start_counter = 'T',

    /**
     * Current counter difference
     * Difference of current value of current counter and preceding value with respect to operation using this counter type
     * On first operation after sensor activation current counter difference is equal to current value of current counter
     */
    curr_counter_diff = 'D',

    /**
     * All counter types
     * Wildcard value used to cause including of current counter, buffer counter and start counter into an operation
     */
    all_counters = 0xff,

} __counter_type; // typedef enum __counter_type

/**
 * Indicates the type of the counter
 * Consider as identical to __counter_type
 */
#pragma pack(1)
typedef TypedEnum<__counter_type, uchar> counter_type; // typedef counter_type
#pragma pack()
/**
 * Indicates the type of the count category
 */
typedef enum {

    /**
     * Person with 2 parameters minHeight, maxHeight
     */
    person = 1,

    /**
     * Wheelchairs and strollers without parameters (under licensing)
     */
    wheelchair_and_stroller_01 = 2,

    /**
     * Bicycles with 2 parameters (under licensing)
     */
    bike_01 = 3,

    __first_unused_category_type

} __category_type; // typedef enum __category_type

/**
 * Indicates the type of the count category
 * Consider as identical to __category_type
 */
#pragma pack(1)
typedef TypedEnum<__category_type, uchar> category_type; // typedef category_type
#pragma pack()
/**
 * Indicates the modification of the status
 */
typedef enum {

    /**
     * Added
     */
    added = '+',

    /**
     * Removed
     */
    removed = '-',

    /**
     * Unchanged
     */
    unchanged = '=',

    /**
     * Constant
     */
    constant = 'C',

    /**
     * Unknown
     */
    unknown = '?',

    /**
     * Error
     */
    error = '!',

    __first_unused_status_modification_indicator

} __status_modification_indicator; // typedef enum __status_modification_indicator

/**
 * Indicates the modification of the status
 * Consider as identical to __status_modification_indicator
 */
#pragma pack(1)
typedef TypedEnum<__status_modification_indicator, uchar> status_modification_indicator; // typedef status_modification_indicator
#pragma pack()
/**
 * Indicates the type of the sensor status
 */
typedef enum {

    /**
     * Sabotage
     */
    sabotage = 1,

    /**
     * Primary configuration data is invalid; sensor is running on secondary (backup) configuration
     */
    config_backup_active = 2,

    /**
     * Primary configuration data is valid, but the secondary (backup) configuration is missing or invalid
     */
    config_backup_missing = 3,

    /**
     * The configuration contains one or more parameters with values that do not conform with the respective constraints
     */
    invalid_config_params = 5,

    /**
     * The configuration data are invalid.
     */
    invalid_config = 6,

    /**
     * The sensor is currently running in service mode
     */
    service_mode_active = 4,

    /**
     * The maximum temperature was exceeded at least once.
     */
    over_temperature_detected = 7,

    /**
     * The maximum temperature is exceeded.
     */
    over_temperature_active = 8,

    /**
     * The fpga was restarted.
     */
    fpga_restart = 9,

    /**
     * Undervoltage was detected.
     */
    power_fail = 10,

    /**
     * Only communication is possible, no counting functionality currently available.
     */
    communication_only = 11,

    __first_unused_sensor_status

} __sensor_status; // typedef enum __sensor_status

/**
 * Indicates the type of the sensor status
 * Consider as identical to __sensor_status
 */
#pragma pack(1)
typedef TypedEnum<__sensor_status, uchar> sensor_status; // typedef sensor_status
#pragma pack()
/**
 * Indicates the type of the function area status
 */
typedef enum {

    /**
     * New counting result flag
     */
    new_counting_result = 1,

    /**
     * At least one slave is missing (no timestamp communication)
     */
    slave_missing = 2,

    /**
     * Door is clear (under licensing)
     */
    door_clear = 3,

    /**
     * Door is not clear (firmware feature under licensing)
     */
    door_not_clear = 4,

    __first_unused_function_area_status

} __function_area_status; // typedef enum __function_area_status

/**
 * Indicates the type of the function area status
 * Consider as identical to __function_area_status
 */
#pragma pack(1)
typedef TypedEnum<__function_area_status, uchar> function_area_status; // typedef function_area_status
#pragma pack()
/**
 * Indicates the type of the status led working mode
 */
typedef enum {

    /**
     * Status leds off
     */
    status_led_off = 0,

    /**
     * Status leds works in normal mode as error indicator
     */
    status_led_normal_mode = 1,

    /**
     * Both status leds permanent on
     */
    status_led_both_permanent = 2,

    /**
     * Left status LED permanent on
     */
    status_led_left_permanent = 3,

    /**
     * Right status LED permanent on
     */
    status_led_right_permanent = 4,

    /**
     * "Operation Mode 1" active
     */
    status_led_operation_mode1 = 5,

    /**
     * "Operation Mode 2" active
     */
    status_led_operation_mode2 = 6,

    __first_unused_status_led_work_mode

} __status_led_work_mode; // typedef enum __status_led_work_mode

/**
 * Indicates the type of the status led working mode
 * Consider as identical to __status_led_work_mode
 */
#pragma pack(1)
typedef TypedEnum<__status_led_work_mode, uchar> status_led_work_mode; // typedef status_led_work_mode
#pragma pack()
/**
 * Indicates the type of the hall sensor function
 */
typedef enum {

    /**
     * Combined activation and door function
     */
    activate_and_door_function = 0,

    __first_unused_hall_sensor_function

} __hall_sensor_function; // typedef enum __hall_sensor_function

/**
 * Indicates the type of the hall sensor function
 * Consider as identical to __hall_sensor_function
 */
#pragma pack(1)
typedef TypedEnum<__hall_sensor_function, uchar> hall_sensor_function; // typedef hall_sensor_function
#pragma pack()
/**
 * Indicates the type of the firmware
 */
typedef enum {

    /**
     * Application
     */
    application = 1,

    /**
     * Fpga 1
     */
    fpga_1 = 2,

    /**
     * Fpga 2
     */
    fpga_2 = 3,

    /**
     * Infoblock of application firmware
     */
    infoblock_application = 4,

    /**
     * Infoblock of fpga 1 firmware
     */
    infoblock_fpga_1 = 5,

    /**
     * Infoblock of fpga 2 firmware
     */
    infoblock_fpga_2 = 6,

    __first_unused_firmware_type

} __firmware_type; // typedef enum __firmware_type

/**
 * Indicates the type of the firmware
 * Consider as identical to __firmware_type
 */
#pragma pack(1)
typedef TypedEnum<__firmware_type, uchar> firmware_type; // typedef firmware_type
#pragma pack()
/**
 * Type of Firmware to be Read
 */
typedef enum {

    /**
     * Current Firmware
     */
    activeFirmware = 0,

    /**
     * Backup Firmware
     */
    backupFirmware = 1,

    __first_unused_backup_type

} __backup_type; // typedef enum __backup_type

/**
 * Type of Firmware to be Read
 * Consider as identical to __backup_type
 */
#pragma pack(1)
typedef TypedEnum<__backup_type, uchar> backup_type; // typedef backup_type
#pragma pack()
/**
 * Type of firmware feature
 */
typedef enum {

    /**
     * Undefined firmware feature
     */
    Undefined = 0,

    /**
     * Counter version 2 is available
     */
    CounterVersion2 = 1,

    /**
     * Communication via IBIS-IP protocol is available
     */
    IbisIp = 2,

    /**
     * Signalling of the door clear state is available
     */
    DoorClear = 3,

    /**
     * Signalling of the sabotage detection state is available
     */
    Sabotage = 4,

    /**
     * The sensor supports separation logic
     */
    Separation = 5,

    /**
     * Counting of the person category is supported
     */
    PersonCounting = 6,

    /**
     * Configuring and counting of the bike category is supported
     */
    BikeCounting = 7,

    /**
     * Configuring and counting of the wheelchair category is supported
     */
    WheelchairCounting = 8,

    /**
     * Flashlayout version 3 is available
     */
    FlashLayoutVersion3 = 9,

    /**
     * Communication via IBIS-over-IP protocol is available
     */
    IbisOverIp = 10,

    /**
     * SNMP is available
     */
    Snmp = 11,

    /**
     * Signalling of the sabotage detection state version 2 is available
     */
    SabotageVersion2 = 12,

    /**
     * DHCP is available
     */
    Dhcp = 13,

    __first_unused_firmware_feature_type

} __firmware_feature_type; // typedef enum __firmware_feature_type

/**
 * Type of firmware feature
 * Consider as identical to __firmware_feature_type
 */
#pragma pack(1)
typedef TypedEnum<__firmware_feature_type, uchar> firmware_feature_type; // typedef firmware_feature_type
#pragma pack()
/**
 * Response code to update command
 */
typedef enum {

    /**
     * Updateorder was accepted and the update will start sometime.
     */
    update_accept_status_update_accepted = 1,

    /**
     * URL type unknown
     */
    update_accept_status_url_type_unknown = 2,

    /**
     * The device declined the update order for arbitrary reasons. In most cases it is because there is an update already running.
     */
    update_accept_status_no_updates_allowed = 3,

    __first_unused_update_accept_enumeration

} __update_accept_enumeration; // typedef enum __update_accept_enumeration

/**
 * Response code to update command
 * Consider as identical to __update_accept_enumeration
 */
#pragma pack(1)
typedef TypedEnum<__update_accept_enumeration, uchar> update_accept_enumeration; // typedef update_accept_enumeration
#pragma pack()
/**
 * Update status enumeration
 */
typedef enum {

    /**
     * No update is running
     */
    update_status_no_update = 0,

    /**
     * Preparation for update is running
     */
    update_status_prepare_update_running = 1,

    /**
     * Preparation for update failed
     */
    update_status_prepare_update_failed = 11,

    /**
     * Updateorder was accepted and the update will start sometime.
     */
    update_status_update_accepted = 21,

    /**
     * Download of update file is running
     */
    update_status_download_update_file_running = 2,

    /**
     * Download of update file failed
     */
    update_status_download_update_file_failed = 12,

    /**
     * Update file is corrupted
     */
    update_status_update_file_corrupted = 22,

    /**
     * URL type is unknown
     */
    update_status_url_type_unknown = 32,

    /**
     * Update of firmware is running
     */
    update_status_update_firmware_running = 3,

    /**
     * Switching the indicator for bootable firmware
     */
    update_status_update_firmware_switch_boot_flags = 13,

    /**
     * Update of firmware succeeded, waiting for restart
     */
    update_status_update_firmware_success_wait_for_restart = 23,

    /**
     * Update of configuration is running
     */
    update_status_update_config_running = 4,

    /**
     * Update of configuration succeeded
     */
    update_status_update_config_success_wait_for_restart = 14,

    /**
     * Update of configuration failed, waiting for restart
     */
    update_status_update_config_failed_wait_for_restart = 24,

    /**
     * Installation successful
     */
    update_status_installation_successful = 5,

    /**
     * Installation failed
     */
    update_status_installation_failed = 15,

    /**
     * Update not necessary. Same Firmwareversion already installed.
     */
    update_status_update_not_necessary = 25,

    /**
     * Invalid. This should never show up, if so this is a clear errorcase with should be explained in more Detail inside the same Paylod.
     */
    update_status_invalid = 255,

} __update_status_enumeration; // typedef enum __update_status_enumeration

/**
 * Update status enumeration
 * Consider as identical to __update_status_enumeration
 */
#pragma pack(1)
typedef TypedEnum<__update_status_enumeration, uchar> update_status_enumeration; // typedef update_status_enumeration
#pragma pack()
/**
 * Support Level of Messages
 */
typedef enum {

    /**
     * No Support Level - unclassified (obsolete)
     */
    support_level_not_set = 0,

    /**
     * Support Level 1 are customerrelated Information to solve the Problem by the customer itself. 
     */
    support_level_1 = 1,

    /**
     * Support Level 2 is for the IRIS-technicians and developers only.
     */
    support_level_2 = 2,

    /**
     * request all support level
     */
    support_level_request_all = 255,

} __support_level_enumeration; // typedef enum __support_level_enumeration

/**
 * Support Level of Messages
 * Consider as identical to __support_level_enumeration
 */
#pragma pack(1)
typedef TypedEnum<__support_level_enumeration, uchar> support_level_enumeration; // typedef support_level_enumeration
#pragma pack()
/**
 * OperationTimeCounter enumeration
 */
typedef enum {

    /**
     * Counter for current Uptime in ms. Uptime is the time elapsed since switching on. This counter is automatically reset after each restart.
     */
    operation_time_uptime = 0,

    /**
     * Counter for total Uptime in ms. Totaluptime is the total time the sensor has been switched on. It is the sum of all uptimes. 
     */
    operation_time_total = 1,

    /**
     * Counter for total (summed up) LED-Runtime in ms.
     */
    operation_time_illumination = 2,

    /**
     * Counter for total uptime during overtemperature in ms. This operation time counter contains the duration in which the sensor has been exposed to a temperature that is above the specified maximum temperature. 
     */
    operation_time_over_temperature = 3,

    /**
     * Counter for total uptime during undervoltage in ms.
     */
    operation_time_under_voltage = 4,

    /**
     * Counter for total uptime while counting is running in ms.
     */
    operation_time_counting = 5,

    __first_unused_operation_time_counter_enumeration

} __operation_time_counter_enumeration; // typedef enum __operation_time_counter_enumeration

/**
 * OperationTimeCounter enumeration
 * Consider as identical to __operation_time_counter_enumeration
 */
#pragma pack(1)
typedef TypedEnum<__operation_time_counter_enumeration, uchar> operation_time_counter_enumeration; // typedef operation_time_counter_enumeration
#pragma pack()
/**
 * Log Level Enumeration
 */
typedef enum {

    /**
     * emergency
     */
    log_level_emergency = 0,

    /**
     * fatal
     */
    log_level_fatal = 1,

    /**
     * alert
     */
    log_level_alert = 2,

    /**
     * critical
     */
    log_level_critical = 3,

    /**
     * error
     */
    log_level_error = 4,

    /**
     * warning
     */
    log_level_warning = 5,

    /**
     * notice
     */
    log_level_notice = 6,

    /**
     * info
     */
    log_level_info = 7,

    /**
     * debug
     */
    log_level_debug = 8,

    /**
     * invalid log level
     */
    log_level_invalid = 255,

} __log_level_enumeration; // typedef enum __log_level_enumeration

/**
 * Log Level Enumeration
 * Consider as identical to __log_level_enumeration
 */
#pragma pack(1)
typedef TypedEnum<__log_level_enumeration, uchar> log_level_enumeration; // typedef log_level_enumeration
#pragma pack()
/**
 * Log Info Code Enumeration
 */
typedef enum {

    /**
     * Log entry is not an error
     */
    log_info_code_no_error = 0x00000000,

    /**
     * info code is not set
     */
    log_info_code_not_set = 0xFFFFFFFE,

    /**
     * Invalid info code
     */
    log_info_code_invalid = 0xFFFFFFFF,

} __log_info_code_enumeration; // typedef enum __log_info_code_enumeration

/**
 * Log Info Code Enumeration
 * Consider as identical to __log_info_code_enumeration
 */
#pragma pack(1)
typedef TypedEnum<__log_info_code_enumeration, ulong> log_info_code_enumeration; // typedef log_info_code_enumeration
#pragma pack()
// Structures

/**
 * Structure with counting results, divided into boarding and alighting passengers
 */
#pragma pack(1)
typedef struct _category_counts {

    /**
     * Category ID
     */
    category_id categoryId;

    /**
     * Boarding
     */
    count_result boarding;

    /**
     * Alighting
     */
    count_result alighting;

} category_counts; // typedef struct category_counts
#pragma pack()

/**
 * Structure for category information
 */
#pragma pack(1)
typedef struct _category {

    /**
     * Category ID
     */
    category_id id;

    /**
     * Category number
     */
    category_type descriptionNumber;

    /**
     * Parameter 1
     */
    ushort parameter1;

    /**
     * Parameter 2
     */
    ushort parameter2;

    /**
     * Parameter 3
     */
    ushort parameter3;

    /**
     * Parameter 4
     */
    ushort parameter4;

} category; // typedef struct category
#pragma pack()

/**
 * Door Number
 */
#pragma pack(1)
typedef struct _door_number {

    /**
     * Function Area Address
     */
    ushort functionAreaAddress;

    /**
     * Door Address
     */
    ushort doorAddress;

} door_number; // typedef struct door_number
#pragma pack()

/**
 * Door Status
 */
#pragma pack(1)
typedef struct _door_status {

    /**
     * Function Area Address
     */
    ushort functionAreaAddress;

    /**
     * Door Address
     */
    ushort doorAddress;

    /**
     * Left door status
     */
    door_state leftStatus;

    /**
     * Right door status
     */
    door_state rightStatus;

} door_status; // typedef struct door_status
#pragma pack()

/**
 * Door Status
 */
#pragma pack(1)
typedef struct _door_status_with_old {

    /**
     * Function Area Address
     */
    ushort functionAreaAddress;

    /**
     * Door Address
     */
    ushort doorAddress;

    /**
     * Old left door status
     */
    door_state oldLeftStatus;

    /**
     * Old right door status
     */
    door_state oldRightStatus;

    /**
     * New left door status
     */
    door_state newLeftStatus;

    /**
     * New right door status
     */
    door_state newRightStatus;

} door_status_with_old; // typedef struct door_status_with_old
#pragma pack()

/**
 * Register
 */
#pragma pack(1)
typedef struct _reg {

    /**
     * Register number
     */
    ushort registerNumber;

    /**
     * Register value
     */
    ushort registerValue;

} reg; // typedef struct reg
#pragma pack()

/**
 * Register Address
 */
#pragma pack(1)
typedef struct _reg_addr {

    /**
     * Address
     */
    ulong address;

    /**
     * Value
     */
    ulong value;

} reg_addr; // typedef struct reg_addr
#pragma pack()

/**
 * Sensor Status Notification
 */
#pragma pack(1)
typedef struct _sensorStatusNotification {

    /**
     * Status Indicator
     */
    status_modification_indicator indicator;

    /**
     * Sensor Status
     */
    sensor_status status;

} sensorStatusNotification; // typedef struct sensorStatusNotification
#pragma pack()

/**
 * Function Area Status
 */
#pragma pack(1)
typedef struct _functionAreaStatus {

    /**
     * Function area number
     */
    ushort functionAreaNumber;

    /**
     * Register value
     */
    function_area_status functionAreaStatusBytes;

} functionAreaStatus; // typedef struct functionAreaStatus
#pragma pack()

/**
 * Function Area Status Notification
 */
#pragma pack(1)
typedef struct _functionAreaStatusNotification {

    /**
     * Function area number
     */
    ushort functionAreaNumber;

    /**
     * Status Indicator
     */
    status_modification_indicator indicator;

    /**
     * Register value
     */
    function_area_status functionAreaStatusBytes;

} functionAreaStatusNotification; // typedef struct functionAreaStatusNotification
#pragma pack()

/**
 * Message Type Definition
 */
#pragma pack(1)
typedef struct _messageTypeDef {

    /**
     * Command character
     */
    uchar commandChar;

    /**
     * Command character
     */
    ubyte versionByte;

    /**
     * Sub-command character
     */
    uchar subCommandChar;

} messageTypeDef; // typedef struct messageTypeDef
#pragma pack()

/**
 * Group/Parameter ID
 */
#pragma pack(1)
typedef struct _param_id {

    /**
     * Group ID
     */
    ushort groupId;

    /**
     * Parameter ID
     */
    ushort paramId;

} param_id; // typedef struct param_id
#pragma pack()

/**
 * Data source selector
 */
#pragma pack(1)
typedef struct _selector {

    /**
     * Data source ID
     */
    ulong dataSource;

    /**
     * Activation flag
     */
    bool_flag enabled;

    /**
     * Operational flags
     */
    ulong flags;

} selector; // typedef struct selector
#pragma pack()

// Bit Fields


/**
 * Represents a pixel value made up of flags (4 bits) and measure result (12 bits)
 */
#pragma pack(1)
typedef struct {

    /**
     * The measure result for the pixel
     */
    ushort value : 12;

    /**
     * The pixel flags
     */
    ubyte flags : 4;

} px_val; // typedef struct px_val
#pragma pack()

/**
 * CanIrma address
 */
#pragma pack(1)
typedef struct {

    /**
     * Device address
     */
    ulong address : 19;

    /**
     * Receiver recognition
     */
    uchar receiver : 3;

} can_irma_adr; // typedef struct can_irma_adr
#pragma pack()

/**
 * UIP Message Byte Version + Level
 */
#pragma pack(1)
typedef struct {

    /**
     * Level
     */
    uchar level : 4;

    /**
     * Version
     */
    uchar version : 4;

} uip_level; // typedef struct uip_level
#pragma pack()

/**
 * UIP Message Length
 */
#pragma pack(1)
typedef struct {

    /**
     * Message Length
     */
    ushort length : 15;

    /**
     * Repeat Message Flag 
     */
    uchar repeat : 1;

} uip_length; // typedef struct uip_length
#pragma pack()
// Arrays

/**
 * An array of 500 pixel values (16Bit)
 */
typedef px_val px_array_16Bit[500];

/**
 * An array of 500 pixel values (8Bit)
 */
typedef uchar px_array_8Bit[500];

/**
 * An array of 16 bytes, forming a string
 */
typedef char char_array_16Bytes[16];

/**
 * An array of 32 bytes, forming a string
 */
typedef char char_array_32Bytes[32];

// Message casting function

} // namespace uip

} // namespace iris


#endif
