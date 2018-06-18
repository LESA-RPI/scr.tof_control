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

#ifndef QT_DIST500LEDPAIR_H
#define QT_DIST500LEDPAIR_H

// Qt includes
#include <QWidget>

class QBoxLayout;

// iris includes
#include "../dist500/DoorState.h"

// iris forward declarations
namespace iris {
    namespace dist500 {
        class Dist500Led;
    }
}

namespace iris {

namespace qt {

class Dist500Led;

/**
 * This class implements a Qt widget with two Dist500Led widgets. It can be connected
 * to a QtDist500 instance and show the door state with the LEDs acting in alternating
 * manner.
 */
class SENSORAPIQT Dist500LedPair : public QWidget {

    Q_OBJECT

    Q_PROPERTY (Qt::Orientation orientation READ orientation WRITE setOrientation)

    Q_PROPERTY(unsigned char sensorNo READ sensorNo WRITE setSensorNo)

protected:

    /**
     * Holds the layout instance
     */
    QBoxLayout *layout;

    /**
     * Holds the LED widget for the "door open" state
     */
    Dist500Led* openLed;
    /**
     * Holds the LED widget for the "door closed" state
     */

    Dist500Led* closeLed;

    /**
     * Holds the current Orientation property value
     */
    Qt::Orientation activeOrientation;

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
    Dist500LedPair(QWidget *parent = 0);

    /**
     * Returns the Orientation property
     *
     * @return Current orientation
     */
    Qt::Orientation orientation(void) const;

    /**
     * Sets the value of the orientation property
     *
     * @param newOrientation New orientation to be set
     */
    void setOrientation(Qt::Orientation newOrientation);

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

    void openClicked(void);

    void closeClicked(void);

}; // namespace Dist500LedPair

} // namespace qt

} // namespace iris

#endif // QT_DIST500LEDPAIR_H
