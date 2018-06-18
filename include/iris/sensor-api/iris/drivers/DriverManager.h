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

#ifndef DRIVERS_DRIVERMANAGER_H
#define DRIVERS_DRIVERMANAGER_H

// STL includes
#include <map>
#include <string>
#include <vector>

// iris includes
#include "iris/Common.h"
#include "iris/drivers/Driver.h"
#include "iris/sharedlibs/SharedLib.h"
#include "iris/synchronization/Mutex.h"

namespace iris {

namespace drivers {

// forward declation to prevent #include cycles
class Sensor;

/**
 * Manages a list of loaded Driver instances
 */
class SENSORAPI DriverManager {

public:

    /**
     * Contains the list of loaded drivers
     */
    typedef std::vector<Driver*> DriverList;

    /**
     * Returns the global DriverManager instance
     *
     * @return Reference to static instance
     *
     * @note Singleton pattern
     */
    static DriverManager& getInstance(void);

    /**
     * Loads the given driver
     *
     * @param driverLibName File name of the driver library
     * @param activate Activation flag (<code>true</code>
     *        results in activation after loading,
     *        <code>false</code> only loads the driver)
     *
     * @return Driver instance
     *
     * @throw Exception if driver cannot be loaded
     */
    Driver& loadDriver(const std::string& driverLibName, const bool activate = true);

    /**
     * Loads all drivers found in the given directory.
     * Drivers in subdirectories can be included if desired
     *
     * @param driverLibPath Path containing the driver libraries
     * @param activate Activation flag (<code>true</code>
     *        results in activation after loading,
     *        <code>false</code> only loads the driver)
     * @param recursive Flag indicating if sub-directories should be searched
     *        as well
     *
     * @return List of successfully loaded drivers
     */
    DriverList loadDrivers(const std::string& driverLibPath, bool activate = true, const bool recursive = true);

    /**
     * Unloads the given driver and frees its resources.
     * The Driver instance itself is also freed
     *
     * @param driver Driver to be unloaded
     *
     * @note References to the driver are invalid after that operation
     */
    void unloadDriver(Driver& driver);

    /**
     * Checks whether the given driver is valid
     *
     * @param driver Driver to be checked
     *
     * @return <code>true</code> is valid, <code>false</code> otherwise
     */
    bool isValid(const Driver& driver);

    /**
     * Retrieves a list of the currently known drivers
     *
     * @return Driver list
     */
    DriverList getKnownDrivers(void);

    /**
     * Checks whether any driver is loaded that handles the given URL prefix
     *
     * @param mnemonic URL prefix (without :// separator)
     *
     * @return <code>true</code> if a matching driver is loaded,
     *         <code>false</code> otherwise
     */
    bool isMnemonicKnown(const std::string& mnemonic) const;

    /**
     * Returns a reference to the driver which handles the given URL prefix
     *
     * @param mnemonic URL prefix (without :// separator)
     *
     * @return Driver
     *
     * @throw Exception if no matching driver is loaded
     */
    Driver& getDriverFor(const std::string& mnemonic);

    /**
     * Creates a full URL string from the given components
     *
     * @param urlPrefix URL prefix (without :// separator)
     * @param addr Sensor address (without :// separator)
     *
     * @return Full URL string (prefix://address)
     */
    std::string makeUrl(const std::string& urlPrefix, const std::string &addr) const;

    /**
     * Splits up a full URL into its components
     *
     * @param url URL to be split (prefix://address)
     * @param urlPrefix String receiving the URL prefix (without :// separator)
     * @param addr String receiving the sensor address (without :// separator)
     *
     * @throw Exception if URL is invalid
     */
    void splitUrl(const std::string& url, std::string& urlPrefix, std::string& addr) const;

    /**
     * @brief splitAddress
     * @param addr
     * @param addrCommon
     * @param addrUip
     */
    void splitAddress(const std::string& addr, std::string& addrCommon, std::string& addrUip) const;

    /**
     * Checks whether the given URL is valid
     *
     * @param url Full sensor URL
     *
     * @return <code>true</code> if URL is valid, <code>false</code> otherwise
     */
    bool isUrlValid(const std::string& url);

    /**
     * Returns a Sensor object for the given URL
     *
     * @param url Full sensor URL
     *
     * @return Sensor instance
     *
     * @throw Exception if no matching driver is loaded or if URL is invalid
     *
     * @note The given URL will automatically be enabled (and reset to its
     *       current enable state if something in case of failure)
     */
    Sensor& getSensorFor(const std::string& url);

    /**
     * Constant to check dynamic library against iris driver interface.
     * Equals 0x53495249 which reads "iris" in little endian notation
     */
    static const int magicNumber;

    /**
     * Performs sensor address scan for driver given by URL prefix
     *
     * @param mnemonic URL prefix (without :// separator)
     * @param enable Communication enable flag (<code>true</code>
     *        enables all found addresses for subsequent communication,
     *        <code>false</code> disables all found addresses for subsequent communication)
     * @param userData User-defined additional parameter for callback
     * @param callback Callback for sensor address scan
     */
    Driver::AddressList scanDriverDevices(const std::string& mnemonic, const bool enable = false, void* userData = 0, Driver::SCAN_CALLBACK callback = 0);

    /**
     * Performs sensor address scans for all known drivers.
	 * Callback and related user-defined parameter not used
     *
     * @param enable Communication enable flag (<code>true</code>
     *        enables all found addresses for subsequent communication,
     *        <code>false</code> disables all found addresses for subsequent communication)
     */
    Driver::AddressList scanAllDevices(const bool enable = false);

    /**
     * Adds given driver to the map of known drivers
     *
     * @param driver Driver instance
     * @param activate Activation flag (<code>true</code>
     *        results in activation after registering,
     *        <code>false</code> only registers the driver)
     *
     * @throw Exception if driver is already registered or driver handles an already registered URL prefix
     */
    void registerDriver(Driver& driver, const bool activate = true);

    /**
     * Removes given driver from the map of known drivers
     *
     * @param driver Driver instance
     * @param deactivate Deactivation flag (<code>true</code>
     *        results in deactivation after unregistering,
     *        <code>false</code> only unregisters the driver)
     *
     * @throw Exception if driver matches by mnemonic (URL prefix), but the instance is different
     */
    void unregisterDriver(Driver& driver, const bool deactivate = true);

    /**
     * Checks whether the driver was loaded from a driver library
     *
     * @return <code>true</code> if driver was loaded from a driver library, <code>false<</code>
     *         otherwise
     */
    bool isDynamic(Driver& driver);

    /**
     * Activates default drivers (currently ICEF, UDP and CAN) if possible.
	 * If necessary static Driver instance is created and driver is registered
     *
     * @param noIcefPriority Flag controlling handling of UDP driver
     *        (<code>true</code> UDP driver is created and activated in addition to ICEF driver,
     *        <code>false</code> only ICEF driver is created and activated)
     * @param noCanActivation Flag controlling activation of CAN driver
     *        (<code>true</code> CAN driver is not activated,
     *        <code>false</code> CAN driver is activated
     *
     * @throw Exception if none of the default drivers could be activated
     */
    void createAndActivateDefaultDrivers(const bool noIcefPriority = false, const bool noCanActivation = false);

protected:

    /**
     * Constructor.
     *
     * @note Non-public to enforce singleton
     */
    DriverManager();

    /**
     * Destructor.
     *
     * @note Non-public to enforce singleton
     */
    virtual ~DriverManager();

    /**
     * Maps URL prefixes to Driver instances
     */
    typedef std::map<std::string, Driver*> KnownDrivers;

    /**
     * Standard C function signature for callback function inside dynamic
     * library which implements a Driver instance factory
     */
    typedef Driver* (*CreateInstanceFunc)(void);

    /**
     * Map of loaded drivers
     */
    KnownDrivers knownDrivers;

    typedef std::map<std::string, bool> DynamicDrivers;

    DynamicDrivers dynamicDrivers;

    /**
     * Checks if the given SharedLib instance represents a driver library.
     * Tests for conformity with the iris driver interface
     */
    bool isDriver(const iris::sharedlibs::SharedLib& lib, CreateInstanceFunc& cif);

    /**
     * Standard C funtion signature for callback function inside dynamic library
     * which need to return the correct magic number
     *
     * @see magicNumber
     */
    typedef int (*MagicNumberFunc)(void);

    /**
     * Mutex to synchronize access to knownDrivers member
     */
    iris::synchronization::Mutex mutex;

    /**
     * Global SharedLibManger instance
     *
     * @note Singleton
     */
    static DriverManager* instance;

    /**
     * String constant for the URL separator "://"
     */
    static const std::string urlSeparator;

    typedef std::map<std::string, iris::synchronization::Mutex*> GroupMutexMap;

    typedef std::map<Driver*, iris::synchronization::Mutex*> DriverMutexMap;

    GroupMutexMap groupMutexes;

    DriverMutexMap driverMutexes;

public:

    iris::synchronization::Mutex& getExclusionGroupMutex(const Driver& driver);

    bool shutdownAllDrivers(const bool suppressExceptions = false);

}; // class DriverManager

} // namespace drivers

} // namespace iris

#endif // DRIVERS_DRIVERMANAGER_H
