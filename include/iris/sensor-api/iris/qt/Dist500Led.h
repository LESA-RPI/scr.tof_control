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

#ifndef QT_DIST500LED_H
#define QT_DIST500LED_H

// Qt includes
#include <QWidget>

// Qt forward declarations
class QMouseEvent;

// iris includes
#include "../dist500/DoorState.h"

// forward declarations
class Led;

namespace iris {

namespace qt {

/**
 * Implements a Qt widget with an LED-like indicator; the widget can be connected to a
 * QtDist500 instance and react on door state changes
 */
class SENSORAPIQT Dist500Led : public QWidget {

    Q_OBJECT

    Q_ENUMS (IndicationMode)

    Q_PROPERTY(IndicationMode indicationMode READ indicationMode WRITE setIndicationMode)

    Q_PROPERTY(unsigned char sensorNo READ sensorNo WRITE setSensorNo)

public:

    /**
     * Defines the door state represented by this widget
     */
    enum IndicationMode {

        /**
         * The LED represents the "door open" state
         */
        IndicateOpenDoor,

        /**
         * The LED represents the "door closed" state
         */
        IndicateClosedDoor
    };

protected:

    /**
     * Holds the InstallationMode property value
     */
    IndicationMode activeMode;

    /**
     * Indicates whether the last known state is open (<code>true</code>) or closed
     * (<code>false</code>)
     */
    bool currentlyOpen;

    /**
     * Flag indicating the "knowledge status" of the widget (<code>true</code> means that
     * we have received a door state at least once, <code>false</code> means that we
     * haven't)
     */
    bool stateKnown;

    /**
     * Holds the Led instance (from AnalogWidgets library)
     */
    Led* led;

    /**
     * Returns the recommended size for the widget
     *
     * @return Recommended size
     */
    QSize sizeHint(void) const;

    /**
     * Updates the digit file property of the Counter Widget
     */
    void updateColors(void);

    unsigned char activeSensorNo;

    void mousePressEvent(QMouseEvent *event);

public:

    /**
     * Constructor
     *
     * @param parent Parent widget
     */
    Dist500Led(QWidget* parent = 0);

    /**
     * Sets the IndicationMode property
     *
     * @param mode New mode to be set
     */
    void setIndicationMode(IndicationMode mode);

    /**
     * Returns the current IndicationMode property
     *
     * @value Current IndicationMode value
     */
    IndicationMode indicationMode(void) const;

    unsigned char sensorNo(void) const;

    void setSensorNo(const unsigned char no);

public slots:

    /**
     * Processes a DoorState
     *
     * @param state State to be processed
     */
    void newDoorState(const iris::dist500::DoorState& state);

    /**
     * Resets the state to "unknown"
     */
    void reset(void);

signals:

    void clicked(void);

}; // class Dist500Led

} // namespace qt

} // namespace iris

#endif // QT_DIST500LED_H
