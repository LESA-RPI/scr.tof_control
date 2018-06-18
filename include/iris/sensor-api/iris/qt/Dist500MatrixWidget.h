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

#ifndef QT_DIST500MATRIXWIDGET_H
#define QT_DIST500MATRIXWIDGET_H

// Qt includes
#include <QTransform>

class QResizeEvent;

// iris includes
#include "Dist500BaseWidget.h"

namespace iris {

namespace qt {

/**
 * This class implements a Qt widget rendering a false-color pixel matrix from
 * the sensor data. Several options allow for customization and the optional
 * overlay of additional data
 */
class SENSORAPIQT Dist500MatrixWidget : public ImageBufferedDist500BaseWidget
{

    Q_OBJECT

    Q_ENUMS(ValueMode TimestampUnit Mirroring)

    Q_PROPERTY(int pixelSize READ pixelSize WRITE setPixelSize)
    Q_PROPERTY(bool showCross READ showCross WRITE setShowCross)
    Q_PROPERTY(bool showPictureNumber READ showPictureNumber WRITE setShowPictureNumber)
    Q_PROPERTY(bool showTimestamp READ showTimestamp WRITE setShowTimestamp)
    Q_PROPERTY(bool showCoordinates READ showCoordinates WRITE setShowCoordinates)
    Q_PROPERTY(ValueMode pictureNumberMode READ pictureNumberMode WRITE setPictureNumberMode)
    Q_PROPERTY(ValueMode timestampMode READ timestampMode WRITE setTimestampMode)
    Q_PROPERTY(TimestampUnit timestampUnit READ timestampUnit WRITE setTimestampUnit)
    //Q_PROPERTY(bool drawCentric READ drawCentric WRITE setDrawCentric)
    Q_PROPERTY(Mirroring mirroring READ mirroring WRITE setMirroring)

public:

    /**
     * Defines the way in which picture number and timestamp values will be displayed
     */
    enum ValueMode {

        /**
         * Absolute values (as sent by the sensor) are used
         */
        ValueMode_Absolute,

        /**
         * Relative values in relation to the values at a given start point will be displayed;
         * this start points (base values) are usually the one of the first picture received
         * in an installation mode session
         */
        ValueMode_Relative

    };

    /**
     * Defines the possible units for timestamp display
     */
    enum TimestampUnit {

        /**
         * Timestamps are expressed in seconds
         */
        TimestampUnit_Seconds,

        /**
         * Timestamps are expressed in milliseconds
         */
        TimestampUnit_Millis

    };

    /**
     * Constructor
     *
     * @param parent Parent widget
     */
    Dist500MatrixWidget(QWidget *parent = 0);

    /**
     * Returns the size of a DIST500 matrix pixel represenation on screen
     * (pixels are squares, so the same size applies to width and height)
     *
     * @return Size in screen pixels
     */
    int pixelSize(void) const;

    /**
     * Returns the showCross property value
     *
     * @param Current showCross flag (<code>true</code>: show coordinate
     *        cross, <code>false</code>: hide cross)
     */
    bool showCross(void) const;

    /**
     * Returns the showPictureNumber property value
     *
     * @return Current showPictureNumber flag (<code>true</code>: show
     *         picture number, <code>false</code>; hide picture number)
     */
    bool showPictureNumber(void) const;

    /**
     * Returns the current mode for picture number displaying (absolute
     * or relative)
     *
     * @return Current picture number mode setting
     */
    ValueMode pictureNumberMode(void) const;

    /**
     * Returns the current mode for timestamp displaying (absolute
     * or relative)
     *
     * @return Current timestamp mode setting
     */
    ValueMode timestampMode(void) const;

    /**
     * Returns the current showTimestamp property value
     *
     * @return Timestamp display flag (<code>true</code>: show timestamps,
     *         <code>false</code>: don't show timestamps)
     */
    bool showTimestamp(void) const;

    /**
     * Returns the current showCoordinates property value
     *
     * @return Timestamp display flag (<code>true</code>: show coordinates,
     *         <code>false</code>: don't show coordinates)
     */
    bool showCoordinates(void) const;

    /**
     * Returns the currently active timestampUnit property
     *
     * @return Active timestamp unit (secs or millisecs)
     */
    TimestampUnit timestampUnit(void) const;

    /**
     * Returns the current coordinate cross position
     *
     * @return Coordinate cross position in sensor pixel coordinates
     *         (0..24, 0..25)
     */
    QPoint coordinates(void) const;

    /*void setCoordinates(QPoint& coordinates);

    void setCoordinates(int x, int y);*/

    //bool drawCentric(void) const;

    /**
     * Defines the mirroring options applicable to the widget rendering
     * (takes effect <i>before<i> orientation settings are applied, if any)
     */
    enum Mirroring {

        /**
         * Unmirrored (default)
         */
        Mirroring_None,

        /**
         * Mirrored along X axis (of sensor image)
         */
        Mirroring_X,

        /**
         * Mirrored along Y axis (of sensor image)
         */
        Mirroring_Y

    }; // enum Mirroring

    /**
     * Sets the Mirroring property
     *
     * @param mirroring New Mirroring to be used
     */
    void setMirroring(Mirroring mirroring);

    /**
     * Returns the current Mirroring property value
     *
     * @param Active Mirroring
     */
    Mirroring mirroring(void) const;

public slots:

    /**
     * Sets the size of the rendered pixels on screen
     */
    void setPixelSize(int pixelSize);

    /**
     * Enables or disables the coordinate cross overlay
     *
     * @param showCross New flag value (<code>true</code: show cross,
     *        <code>false/code>: don't show cross)
     */
    void setShowCross(bool showCross);

    /**
     * Enables or disables the picture number overlay
     *
     * @param showPictureNumber New flag value (<code>true</code: show
     *        picture number, <code>false/code>: don't show number)
     */
    void setShowPictureNumber(bool showPictureNumber);

    /**
     * Sets the desired mode for the picture number overlay
     *
     * @param New mode to be set
     */
    void setPictureNumberMode(ValueMode pictureNumberMode);

    /**
     * Sets the desired mode for the timestamp overlay
     *
     * @param New mode to be set
     */
    void setTimestampMode(ValueMode timestampMode);

    /**
     * Enables or disables the timestamp overlay
     *
     * @param showTimestamp New flag value (<code>true</code: show
     *        timestamp, <code>false/code>: don't show number)
     */
    void setShowTimestamp(bool showTimestamp);

    /**
     * Enables or disables the cross coordinate overlay
     *
     * @param showCross New flag value (<code>true</code: show position,
     *        <code>false/code>: don't show position)
     */
    void setShowCoordinates(bool showCoordinates);

    /**
     * Sets the unit for timestamp display
     *
     * @param timestampUnit Desired unit (secs or millisecs)
     */
    void setTimestampUnit(TimestampUnit timestampUnit);

    //void setDrawCentric(bool drawCentric);

signals:

    /**
     * This signal is emitted whenever the user moves the coorsinate cross
     * to a new position
     *
     * @param coordinates New cross position
     */
    void coordinatesChanged(QPoint coordinates);

    /**
     * This signal is emitted during a redraw after the pixel bitmap has been painted, but
     * before the overlay elements (cursor cross, text labels) - if any - are drawn.
     *
     * @param painter QPainter instance to be used
     * @param pixelSize Height/width (in screen pixels) of a DIST500 pixel in the visualization
     */
    void makeTinoHappy(QPainter& painter, const int pixelSize);

    void pixelDoubleClicked(QPoint coordinate);

    void pixelClicked(QPoint coordinate);

protected:

    /**
     * Handler for Qt paint events
     *
     * @param evt QPaintEvent with detail information
     */
    void paintEvent(QPaintEvent *evt);

    /**
     * Handler for Qt mouse press events
     *
     * @param evt QMouseEvent with detail information
     */
    void mousePressEvent(QMouseEvent *evt);

    /**
     * Returns a size hint (in normal 0 degrees orientation)
     *
     * @return Optimal size
     *
     * @see Dist500BaseWidget::internalSizeHint()
     */
    QSize internalSizeHint() const;

    /**
     * Holds the pixel size property value
     */
    int activePixelSize;

    /**
     * Holds the showCross property value
     */
    bool activeShowCross;

    /**
     * Holds the showPictureNumber property value
     */
    bool activeShowPictureNumber;

    /**
     * Holds the picture number mode property
     */
    ValueMode activePictureNumberMode;

    /**
     * Holds the timestamp mode property
     */
    ValueMode activeTimestampMode;

    /**
     * Holds the showTimestamp property
     */
    bool activeShowTimestamp;

    /**
     * Holds the showCoordinates property
     */
    bool activeShowCoordinates;

    /**
     * Holds the timestamp display unit
     */
    TimestampUnit activeTimestampUnit;

    /**
     * This method is called when pixel data and/or settings have changed
     * in a way that require re-rendering
     *
     * @param triggerUpdateEvent Indicates whether an on-screen update is
     *        necessary or not
     */
    void updateImage(bool triggerUpdateEvent = true);

    /**
     * Holds the coordinates of the cross overlay
     */
    QPoint activeCoordinates;

    void mouseDoubleClickEvent(QMouseEvent *);

    void resizeEvent(QResizeEvent *);

    bool activeDrawCentric;

    QTransform inverseTransform;

    void prepareSizeChange(const QSize size);

    void translateCoordinate(int& x, int& y) const;

    /**
     * Holds the current value of the Mirroring property
     */
    Mirroring activeMirroring;

}; // class Dist500MatrixWidget

} // namespace qt

} // namespace iris

#endif // QT_DIST500MATRIXWIDGET_H
