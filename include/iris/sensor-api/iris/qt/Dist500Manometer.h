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

#ifndef QT_DIST500MANOMETER_H
#define QT_DIST500MANOMETER_H

// Qt includes
#include <QWidget>

// iris includes
#include "../dist500/RegisterValues.h"

// forward declarations
class ManoMeter;

namespace iris {

namespace qt {

/**
 * Implements a Manometer-like sensor temperature Qt widget; it can be connected
 * to a QtDist500 instance to automatically update on temperature changes
 * reported to the PC
 */
class SENSORAPIQT Dist500Manometer : public QWidget {

    Q_OBJECT

    Q_PROPERTY(unsigned char sensorNo READ sensorNo WRITE setSensorNo)

protected:

    /**
     * Defines the number of temperature values to be used for mean computation
     */
    static const int numValues = 1; //80;

    /**
     * Stores the temperature values for mean computation
     */
    int tempValues[numValues];

    /**
     * Counts the number of values for mean computation
     */
    int tempValueCount;

    /**
     * Holds the ManoMeter widget instance (from AnalogWidgets library)
     */
    ManoMeter* manometer;

    /**
     * Returns the recommended size for the widget
     *
     * @return Recommended size
     */
    QSize sizeHint(void) const;

    unsigned char activeSensorNo;

public:

    /**
     * Constructor
     *
     * @param parent Parent widget
     */
    Dist500Manometer(QWidget* parent = 0);

    unsigned char sensorNo(void) const;

    void setSensorNo(const unsigned char no);

public slots:

    /**
     * Processes a RegisterValues instance
     *
     * @param values RegisterValues to be processed
     */
    void newRegisterValues(iris::dist500::RegisterValues values);

}; // class Dist500Manometer

} // namespace qt

} // namespace iris

#endif // QT_DIST500MANOMETER_H
