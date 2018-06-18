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

#ifndef DIST500_COUNTERCONTROLLER_H
#define DIST500_COUNTERCONTROLLER_H

// STL includes
#include <list>
#include <set>

// iris includes
#include "iris/Common.h"
#include "iris/dist500/Dist500Base.h"
#ifdef APIBUILD
    #include "UipTypes.h"
#else
    #include "../UipTypes.h"
#endif
#include "iris/dist500/CountResultSource.h"

namespace iris {

namespace dist500 {

/**
 * This class represents the counting modules' functionality within the DIST500 sensor
 */
class SENSORAPI CounterController: virtual public Dist500Base, public CountResultSource {

public:

    /**
     * Constructor
     *
     * @param sensor reference from driver framework
     */
    CounterController(iris::drivers::Sensor& sensor);

    /**
     * List of function area statuses
     */
    typedef std::list<iris::uip::functionAreaStatus> FunctionAreaStatusList;

    /**
     * Retrieves the function area status(es)
     *
     * @param statusList Reference to list of function area statuses receiving the data
     *
     * @return Operation result
     * @note some statuses are dependent on licensing
     * @see getSensorStatuses
     */
    SENSOR_RESULT getFunctionAreaStatuses(FunctionAreaStatusList& statusList);

    /**
     * Set of sensor statuses
     */
    typedef std::set<iris::uip::sensor_status> SensorStatusSet;

    /**
     * List of sensor status notifications
     */
    typedef std::list<iris::uip::sensorStatusNotification> SensorStatusNotificationList;

    /**
     * Retrieves the sensor status(es)
     *
     * @param statusSet Output set that receives sensor statuses (__sensor_status).
     *
     * @return Operation result
     * @see resetSensorStatuses
     * @see __sensor_status
     * @see getFunctionAreaStatuses
     */
    SENSOR_RESULT getSensorStatuses(SensorStatusSet& statusSet);

    /**
     * Resets the sensor status(es)
	 * List of sensor status notifications informs about actual changes of sensor status(es)
     *
     * @param statusSet Const reference to set of sensor statuses (SensorStatusSet)
     * @param statusNotificationList Reference to list of sensor status notifications (SensorStatusNotificationList)
     *
     * @return Operation result
     * @note this request is not repeated automatically after a timeout because of the risk of status changes in between not getting detected
     */
    SENSOR_RESULT resetSensorStatuses(const SensorStatusSet& statusSet, SensorStatusNotificationList& statusNotificationList);

    /**
     * List of count results (per category)
     */
    typedef std::list<iris::uip::category_counts> CountList;

    /**
     * Retrieves the count results
     *
     * @param functionArea Function area number
     * @param counterType Counter type
     * @param resetFlag <code>true</code> resets the data after retrieval,
     *        <code>false</code> remains them untouched
     * @param categoryId Category ID
     * @param countList Reference to CountList receiving the data
     *
     * @return Operation result
     * @see setCountResults
     * @see resetCounts
     */
    SENSOR_RESULT getCountResults(unsigned short functionArea, iris::uip::counter_type counterType, bool resetFlag, unsigned char categoryId, CountList& countList);

    /**
     * Sets the count results (for debugging purposes)
     *
     * @param functionArea Function area number
     * @param counterType Counter type
     * @param countingFinished Flag indicating whether the counting-finished
     *        flag is to be set along with the counts (<code>true</code> set
     *        flag, <code>false</code> don't set flag)
     * @param countList Reference to CountList containing the data
     *
     * @return Operation result
     * @see getCountResults
     * @see resetCounts
     */
    SENSOR_RESULT setCountResults(unsigned short functionArea, iris::uip::counter_type counterType, bool countingFinished, const CountList& countList);

    /**
     * Requests reset of the boarding/alighting counters
     *
     * @param functionArea Function area number
     * @param counterType Counter type
     *
     * @return Operation result
     * @see getCountResults
     * @see setCountResults
     */
    SENSOR_RESULT resetCounts(const unsigned short functionArea, iris::uip::counter_type counterType);

    /**
     * Starts counting
     *
     * @return Operation result
     * @see stopCounting
     */
    SENSOR_RESULT startCounting(void);

    static bool broadcastStartCounting(void);

    static bool broadcastStopCounting(void);

    /**
     * Stops counting
     *
     * @return Operation result
     * @see startCounting
     */
    SENSOR_RESULT stopCounting(void);

    /**
     * List of count categories
     */
    typedef std::list<iris::uip::category> CategoryList;

    /**
     * Retrieves the supported count categories
	 *
     * @param functionArea Function area number
     * @param categoryList Reference to list of count categories receiving the data
     *
     * @return Operation result
     * @note some counting categories are under licensing
     * @see getKnownCategoryTypes
     */
    SENSOR_RESULT getCountCategories(unsigned short functionArea, CategoryList& categoryList);

    /**
     * Set of count category types
     */
    typedef std::set<iris::uip::category_type> CategoryTypeSet;

    /**
     * Retrieves the known count category types
     *
     * @param typeSet Reference to set of count category types receiving the data
     *
     * @return Operation result
     * @see getCountCategories
     */
    SENSOR_RESULT getKnownCategoryTypes(CategoryTypeSet& typeSet);

    /**
     * Checks whether the given count category is acceptable. The sensor may reject categories due to value range infractions or licensing issues.
     *
     * @param categoryDefinition Const reference to count category
     * @param accepted Acceptance flag (<code>true</code>
     *        if category is acceptable, <code>false</code> otherwise)
     *
     * @return Operation result
     */
    SENSOR_RESULT checkCategoryDefinitionAcceptance(const iris::uip::category& categoryDefinition, bool& accepted);

protected:

    /**
     * Callback function for spontaneous messages (sub-command *), here only for C 6.0
     * 
     *
     * @param base Dist500Base instance (surrogate for this pointer)
     * @param message Spontaneously received message
     */
    static void handleSpontaneousCountMessage(Dist500Base* base, UipMessage* message);

}; // class CounterController

} // namespace dist500

} // namespace iris

#endif // DIST500_COUNTERCONTROLLER_H
