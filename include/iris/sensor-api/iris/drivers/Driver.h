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

#ifndef DRIVERS_DRIVER_H
#define DRIVERS_DRIVER_H

// STL includes
#include <map>
#include <set>
#include <string>

// boost includes
#ifndef UNDER_CE
    #include <boost/regex.hpp>
#endif

// iris includes
#include "iris/Common.h"
#include "iris/drivers/Connection.h"
#include "iris/dist500/SensorGroup.h"
#include "iris/dist500/Dist500.h"
#include "iris/synchronization/Mutex.h"

// internal class forwards
#ifndef DONT_DECLARE_UIPMESSAGE
    class UipMessage;
#endif

namespace iris {

namespace drivers {

class DriverManager;

/**
 * Represents a physical connection driver to communicate via UIP, eg on top of
 * UDP or ICEF
 */
class SENSORAPI Driver {

protected:

    class OptionValidator {
    public:
        virtual bool validate(const std::string& value) = 0;
        virtual ~OptionValidator() {}
    };

    class RegExValidator: public OptionValidator {
    protected:
#ifndef UNDER_CE
        const boost::regex regEx;
#else
        const std::string regEx;
#endif
    public:
        RegExValidator(const std::string& regEx);
        virtual ~RegExValidator() {}
        virtual bool validate(const std::string& value);
    };

    class IpAddressValidator: public RegExValidator {
    public:
        IpAddressValidator();
        virtual ~IpAddressValidator() {}
    };

    class IpNetworkValidator: public RegExValidator {
    public:
        IpNetworkValidator();
        virtual ~IpNetworkValidator() {}
    };

    class ChoiceValidator: public OptionValidator {
    public:
        typedef std::list<std::string> ChoiceList;
        ChoiceValidator(const ChoiceList& choiceList);
        bool validate(const std::string& value);
    protected:
        ChoiceList choiceList;
    };

    class OnOffOptionValidator: public ChoiceValidator {
    public:
        OnOffOptionValidator();
    protected:
        static ChoiceList makeChoiceList(void);
    };

    class ListValidator: public OptionValidator {
    protected:
        OptionValidator& elementValidator;
    public:
        ListValidator(OptionValidator& elementValidator);
    };

    class IntegerValidator: public RegExValidator {
    protected:
        int min;
        int max;
    public:
        IntegerValidator(int min, int max);
        bool validate(const std::string& value);
    };

    class DoubleValidator: public RegExValidator {
    protected:
        double min;
        double max;
    public:
        DoubleValidator(double min, double max);
        bool validate(const std::string& value);
    };

    typedef std::map<std::string, OptionValidator*> OptionValidatorMap;

    typedef std::map<std::string, std::string> OptionDefaultsMap;

    OptionValidatorMap optionValidators;

    OptionDefaultsMap optionDefaults;

    void registerOption(const std::string& optionName, const std::string& defaultValue, OptionValidator* validator);

    void removeOption(const std::string& optionName);

public:

    void setOption(const std::string& optionName, const std::string& optionValue);
    
    void unsetOption(const std::string& optionName);
    
    void setOptionDefault(const std::string& optionName);

    bool isOptionSet(const std::string& optionName) const;

    std::string getOption(const std::string& optionName, const bool useDefaultIfNotSet = true) const;

    std::string getOption(const std::string& optionName, const std::string& defaultValue) const;

    bool supportsOption(const std::string& optionName) const;

    bool isOptionValid(const std::string& optionName, const std::string& optionValue) const;

    /**
     * Checks whether the driver is active or not
     *
     * @return <code>true</code> if driver is active, <code>false</code>
     *         otherwise
     */
    bool isActive(void) const;

    typedef std::set<std::string> OptionNameSet;

    OptionNameSet getOptionNames(const bool onlySetOptions = false);

protected:

    typedef std::map<std::string, std::string> OptionValuesMap;

    OptionValuesMap options;

    void checkOptionName(const std::string optionName) const;

    void checkOption(const std::string& optionName, const std::string& optionValue) const;

    void setActive(void);

    void setInactive(void);

    /**
     * Descriptive name of the driver
     */
    const std::string name;

    /**
     * Prefix for sensor URLs, without the :// separator
     */
    const std::string urlPrefix;

    /**
     * Version string, eg 1.0.0
     */
    const std::string version;

    /**
     * Regular expression to check for syntactical sensor addresses (without
     * prefix and :// separator)
     */
#ifndef UNDER_CE
    const boost::regex urlAddrRegEx;
#else
    const std::string urlAddrRegEx;
#endif

    bool active;

    friend class DriverManager;

    /**
     * Verifies the validity of the given address.
     * Throws an exception if it is not valid.
     *
     * @param addr Address to be verified
     *
     * @throw Exception if address is invalid
     *
     * @note This method is called internally from several methods to ensure the
     *       validity of address parameters
     */
    void ensureValidAddress(const std::string& addr) const;

    /**
     * Constructor. Initializes a new driver instance with the given set
     */
    Driver(const std::string& name, const std::string& urlPrefix, const std::string& version, const std::string& urlAddrRegEx);

    /**
     * Destructor
     */
    virtual ~Driver();

    /**
     * Creates a new Connection instance for the given address.
     * Will usually be overloaded by concrete driver implementations to provide
     * specialized Connection subclassed.
     *
     * @param addr Sensor address (without prefix and :// separator)
     *
     * @return New Connection instance
     */
    virtual Connection* createConnection(const std::string& addr);

    /**
     * Dispatches an incoming message to the destination sensor
     *
     * @param level UIP level (0..2)
     * @param addr Sensor address
     * @param msg Message to be delivered
     */
    void dispatchMessage(const int level, const std::string& addr, const UipMessage* msg);

    virtual std::string getExclusionGroupName(void) const;

    Connection* getInternalConnection(const std::string& addr);

public:

    /**
     * Returns a connection object for the given sensor address
     *
     * @param addr Sensor address (without prefix and :// separator)
     *
     * @return A connection instance for the given address
     *
     * @throw Exception if the address is invalid
     */
    Connection& getConnection(const std::string& addr);

    /**
     * Returns the driver name
     *
     * @return Driver name
     */
    const std::string getName(void) const;

    /**
     * Returns the URL prefix
     *
     * @return Prefix (without :// separator)
     */
    const std::string getUrlPrefix(void) const;

    /**
     * Returns the driver version
     *
     * @return Version string (eg 1.0.0)
     */
    const std::string getVersion(void) const;

    /**
     * Checks whether the given address is valid or not.
     * The check is performed using the regular expression stored in the
     * urlAddrRegEx field
     *
     * @param addr Address to be checked (without prefix and :// separator)
     *
     * @return <code>true</code> if address is valid, <code>false</code>
     *         otherwise
     */
    bool isAddressValid(const std::string& addr) const;

    /**
     * Holds a list of sensor addresses
     */
    typedef std::list<std::string> AddressList;

    /**
     * Maps addresses to Connection objects
     */
    typedef std::map<std::string, Connection*> ConnectionMap;

    /**
     * Maps main-addresses to Connection objects
     */
    typedef std::multimap<std::string, Connection*> ConnectionMultiMap;

    /**
     * Contains the map of currently active (enabled) main-addresses along with
     * their corresponding Connection objects
     */
    ConnectionMultiMap distinctConnections;

    /**
     * Contains the map of currently active (enabled) addresses along with their
     * corresponding Connection objects
     */
    ConnectionMap activeConnections;

    /**
     * Returns the list of currently active (enabled) addresses
     *
     * @return Address list (without URL prefix and :// separator)
     */
    AddressList getActiveAddresses(void);

    /**
     * Callback for sensor address scan
     *
     * @param userData User-defined additional parameter for callback
     * @param driver Driver instance
     * @param url Full sensor URL
     */
    typedef void (*SCAN_CALLBACK)(void* userData, const Driver& driver, const std::string& url);

    /**
     * Returns the list of all sensors addresses that can currently be found
     *
     * @param userData User-defined additional parameter for callback
     * @param callback Callback for sensor address scan
	 *
     * @return Address list (without URL prefix and :// separator)
     */
    virtual AddressList performAddressScan(void* userData = 0, SCAN_CALLBACK callback = 0) const;

    /**
     * Enables the given address for subsequent communication
     *
     * @param addr Address to be enabled (without URL prefix and :// separator)
     * @param sensorInstance Optional sensor instance to use, otherwise it will be created. Useful when updating an address (e.g. DHCP).
     *
     * @throw Exception if address is invalid
     */
    void enableAddress(const std::string& addr, Sensor* sensorInstance = 0);

    /**
     * Disables the given address for subsequent communication
     *
     * @param addr Address to be disabled (without URL prefix and :// separator)
     * @param keepSensor Prohibits deletion of the associated sensor instance.
     * @param keepConnection Prohibits deletion of the associated connection.
     *
     * @throw Exception if address is invalid
     */
    void disableAddress(const std::string& addr, bool keepSensor = false, bool keepConnection = false);

    /**
     * Enables all given addresses for subsequent communication
     *
     * @param addresses List of addresses to be enabled (without URL prefix and
     * :// separator)
     *
     * @throw Exception if any address in the list is invalid
     */
    void enableAddresses(const AddressList& addresses);

    /**
     * Disables all given addresses for subsequent communication
     *
     * @param addresses List of addresses to be disabled (without URL prefix and
     * :// separator)
     *
     * @throw Exception if any address in the list is invalid
     */
    void disableAddresses(const AddressList& addresses);

    /**
     * Disables all currently enabled addresses
     */
    void disableAllAddresses(void);

    /**
     * Checks whether the given address is currently enabled
     *
     * @param addr Address to be checked (without URL prefix and :// separator)
     *
     * @return <code>true</code> if enabled, <code>false</code>otherwise
     */
    bool isAddressEnabled(const std::string& addr) const;

    /**
     * Initializes the driver
     */
    virtual void startupDriver(void);

    /**
     * Deinitializes the driver
     */
    virtual void shutdownDriver(void);

    /**
     * Sends the given message
     *
     * @param level UIP level (0..2)
     * @param addr Sensor address
     * @param message Message to be sent
     */
    virtual void sendMessage(const int level, const std::string& addr, const UipMessage* message) const;

    /**
     * Sends the given message in broadcast mode
     *
     * @param level UIP level (0..2)
     * @param message Message to be sent
     */
    virtual void sendBroadcastMessage(const int level, const UipMessage* message) const;

    /**
     * Returns the associated Sensor instance
     *
     * @param addr Sensor address
     *
     * @return Sensor instance
     */
    Sensor& getSensor(const std::string& addr);

    /**
     * Indicates if parallel communication with several sensors
     * is supported or not
     *
     * @return Parallel support flag
     */
    virtual bool supportsParallelAccess(void) const;

    typedef std::list<iris::dist500::SensorGroup*> SensorGroupList;

    typedef iris::dist500::Dist500List Dist500List;

    static SensorGroupList groupSensors(const Dist500List sensors);

    iris::synchronization::Mutex& getExclusionGroupMutex(void);

    iris::synchronization::Mutex accessMutex;

    iris::synchronization::Mutex& getAccessMutex(void);

    mutable iris::synchronization::Mutex mutex;

    typedef void (*DEBUG_CALLBACK)(void* userData, const int level, const std::string& addr, const UipMessage* msg);

    void setDebugListener(DEBUG_CALLBACK listener, void* userData = 0);

    void clearDebugListener(void);

protected:

    DEBUG_CALLBACK debugListener;

    void* debugListenerUserData;

}; // class Driver

} // namespace drivers

} // namespace iris

#endif // DRIVERS_DRIVER_H
