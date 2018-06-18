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

#ifndef QT_DIST500COUNTER_H
#define QT_DIST500COUNTER_H

// Qt includes
#include <QWidget>

// iris includes
#include "../dist500/CountResult.h"

// forward declarations
class Counter;

namespace iris {

namespace qt {

/**
 * This class implements a counter widget for use with Qt; the widget can be connected to a QtDist500
 * instance and update itself in reaction to count result signals a a user-definable way
 */
class SENSORAPIQT Dist500Counter : public QWidget {

    Q_OBJECT

    Q_ENUMS (SubCountsSelection)

    Q_PROPERTY (bool Colored READ isColored WRITE setColored)

    Q_PROPERTY (bool Cumulative READ isCumulative WRITE setCumulative)

    Q_PROPERTY (SubCountsSelection subCountsSelection READ subCountsSelection WRITE setSubCountsSelection)

    Q_PROPERTY (int Category READ category WRITE setCategory)

    Q_PROPERTY(unsigned char sensorNo READ sensorNo WRITE setSensorNo)

public:

    /**
     * Specifies a count sub-result (boarding or alighing)
     */
    enum SubCountsSelection {

        /**
         * Refers to a sub-result for boarding passengers
         */
        BoardingCounts,

        /**
         * Refres to a sub-result for alighting passengers
         */
        AlightingCounts

    }; // enum SubCountsSelection

protected:

    /**
     * Counter widget from AnalogWidgets library
     */
    Counter* counter;

    /**
     * Returns the recommended size for the widget
     *
     * @return Recommended size
     */
    QSize sizeHint(void) const;

    /**
     * Flag indicating whether new counts will be summed up (<code>true</code>)
     * or simply replaced (<code>false</code>)
     */

    bool activeCumulative;

    /**
     * This flag controls whether colored digits are displayed (<code>true</code>)
     * or simply white ones (<code>false</code>)
     */
    bool activeColored;

    /**
     * Holds the current category filter for incoming results (0 means no restriction)
     */
    int activeCategory;

    /**
     * Holds the current setting the the sub-counts to be processed
     */
    SubCountsSelection activeSubCountsSelection;

    /**
     * Updates the digit file property of the Counter Widget
     */
    void updateColors(void);

    unsigned char activeSensorNo;

public:

    /**
     * Constructor
     *
     * @param parent Parent widget
     */
    Dist500Counter(QWidget* parent = 0);

    /**
     * Sets the Colored property to a new value
     *
     * @param newColored Coloring flag (<code>true</code>: colored digits, <code>false</code>:
     *        white digits)
     */
    void setColored(bool newColored);

    /**
     * Returns the coloring flag
     *
     * @return Coloring flag (<code>true</code>: colored digits, <code>false</code>:
     *        white digits)
     */
    bool isColored(void) const;

    /**
     * Sets the SubCountsSelection property to a new value
     *
     * @param newSelection Desired sub-count to be processed (boarding or alighting)
     *
     * @note Counts will be reset if the sub-count selection effectively changes
     *
     * @see SubCountsSelection
     */
    void setSubCountsSelection(SubCountsSelection newSelection);

    /**
     * Returns the current SubCountSelection property
     */
    SubCountsSelection subCountsSelection(void) const;

    /**
     * Enables or disables the accumulation of incoming counts
     *
     * @param newCumulative Accumulation flag (<code>true</code> counts will be summed up,
     *        <code>false</code>: only the last count is displayed)
     *
     * @note Counts will be reset if the mode effectively changes
     */
    void setCumulative(bool newCumulative);

    /**
     * Returns the current accumulation property
     *
     * @return Accumulation flag (<code>true</code> counts will be summed up,
     *        <code>false</code>: only the last count is displayed)
     */
    bool isCumulative(void) const;

    /**
     * Sets the filter value for incoming results by their category ID or
     * disables the filter
     *
     * @param newCategory Category id if only results for that specific category shall be
     *        processed; 0 (zero) will disable the filter
     *
     * @note Counts will be reset if the category filter value effectively changes
     */
    void setCategory(int newCategory);

    /**
     * Returns the current category filter property
     *
     * @return Category id enabled for filtering (or 0 if disabled)
     *
     */
    int category(void) const;

    /**
     * Returns the value currently that is currently displayed.
     * Depending on the accumulation
     * property, this may be either the last processed count or the sum of the counts processed
     * since the last reset
     *
     * @see activeCumulative
     */
    int currentDisplayValue(void) const;

    unsigned char sensorNo(void) const;

    void setSensorNo(const unsigned char no);

public slots:

    /**
     * Processes a CountResult
     *
     * @param result CountResult to be processed
     */
    void newCountResult(iris::dist500::CountResult result);

    /**
     * Resets the counter value to 0 (zero)
     */
    void reset(void);

}; // class Dist500Counter

} // namespace qt

} // namespace iris

#endif // QT_DIST500COUNTER_H
