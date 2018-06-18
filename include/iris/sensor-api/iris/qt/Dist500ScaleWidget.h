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

#ifndef QT_DIST500SCALEWIDGET_H
#define QT_DIST500SCALEWIDGET_H

// Qt includes
#include <QWidget>

// iris includes
#include "Dist500BaseWidget.h"

namespace iris {

namespace qt {

/**
 * Implements a Qt widget which renders a detail spectrum-band with a certain
 * pixel value (from a DIST500 picture) overlayed as indicator line.
 */
class SENSORAPIQT Dist500ScaleWidget : public ImageBufferedDist500BaseWidget {

    Q_OBJECT

protected:

    /**
     * Returns a size hint (in normal 0 degrees orientation)
     *
     * @return Optimal size
     *
     * @see Dist500BaseWidget::internalSizeHint()
     */
    QSize internalSizeHint() const;

    /**
     * Holds the coordinates of the pixel of interest
     */
    QPoint activeCoordinates;

    /**
     * This method is called when pixel data and/or settings have changed
     * in a way that require re-rendering
     *
     * @param triggerUpdateEvent Indicates whether an on-screen update is
     *        necessary or not
     */
    void updateImage(bool triggerUpdateEvent = true);

    /**
     * Handler for Qt paint events
     *
     * @param evt QPaintEvent with detail information
     */
    void paintEvent(QPaintEvent *evt);

    /**
     * Returns the coordinates of the detailled pixel
     *
     * @return Coordinates of the pixel from wich details will be pulled
     */
    QPoint coordinates(void) const;

public:

    /**
     * Constructor
     *
     * @param parent Parent widget
     */
    Dist500ScaleWidget(QWidget *parent = 0);

public slots:

    /**
     * Sets the pixel coordinate from which the details will be pulled.
     * This method usuallym serves as a slot for the Dist500MatrixWidget's
     * coordinatesChanged() signal
     *
     * @param coordinates Coordinates of the pixel of interest
     */
    void setCoordinates(QPoint coordinates);

}; // class Dist500ScaleWidget

} // namespace qt

} // namespace iris

#endif // QT_DIST500SCALEWIDGET_H
