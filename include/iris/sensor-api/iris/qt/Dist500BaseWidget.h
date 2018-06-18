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

#ifndef QT_DIST500BASEWIDGET_H
#define QT_DIST500BASEWIDGET_H

// Qt includes
#include <QWidget>
#include <QImage>
#include <QPen>

// iris includes
#include "../dist500/Picture.h"
#include "iris/qt/color_map_terrain_2500.h"

namespace iris {
    namespace qt {
        class SpectrumAccessor;
    }
}

namespace iris {

namespace qt {

/**
 * This is a base class for Qt widgets dealing with DIST500 pixel values. It
 * provides common properties and offers methods dealing with the normally
 * used false-color representation scheme. It also offers support for image
 * caching and for simple control on the rendering (eg factors for pixel values)
 *
 * @note Dist500BaseWidget is abstract; sub-classes need to implement at least
 *       the updateImage() and internalSizeHint() methods
 */
class SENSORAPIQT Dist500BaseWidget : public QWidget {

    Q_OBJECT

    Q_ENUMS(ColorMode PictureMode Orientation)

    Q_PROPERTY(int distanceFactor READ distanceFactor WRITE setDistanceFactor)
    Q_PROPERTY(int amplitudeFactor READ amplitudeFactor WRITE setAmplitudeFactor)
    Q_PROPERTY(ColorMode colorMode READ colorMode WRITE setColorMode)
    Q_PROPERTY(PictureMode pictureMode READ pictureMode WRITE setPictureMode)
    Q_PROPERTY(ColorMode colorMode READ colorMode WRITE setColorMode)
    Q_PROPERTY(Orientation orientation READ orientation WRITE setOrientation)
    Q_PROPERTY(bool showLogo READ showLogo WRITE setShowLogo)
    Q_PROPERTY(bool showPixelValue READ showPixelValue WRITE setShowPixelValue)
    Q_PROPERTY(unsigned char sensorNo READ sensorNo WRITE setSensorNo)

public:

    /**
     * Defines the supported coloring modes
     */
    enum ColorMode {

        /**
         * Values are represented using false-color representation (red-to-blue
         * spectrum); this mode is normally used for distance images
         */
        ColorMode_Spectrum,

        /**
         * Values are represented using a grayscale gradient from black to white;
         * this mode is the default for amplitude pictures
         */
        ColorMode_Grayscale

    }; // enum ColorMode

    /**
     * Defines which sub-picture(s)go(es) into the renderer
     */
    enum PictureMode {

        /**
         * Selects the distance sub-picture
         */
        PictureMode_Distance,

        /**
         * Selecte the amplitude sub-picture
         */
        PictureMode_Amplitude,

        /**
         * Selects both distance and amplitude sub-pictures
         */
        PictureMode_Combined

    }; // enum PictureMode

    /**
     * Defines the supported Orientation of the widget rendering
     * (takes effect <i>after<i> mirroring has been applied, if any)
     */
    enum Orientation {

        /**
         * 0 degrees (default)
         */
        Orientation_0,

        /**
         * 90 degrees
         */
        Orientation_90,

        /**
         * 180 degrees
         */
        Orientation_180,

        /**
         * 270 degrees
         */
        Orientation_270

    }; // enum Orientation

    /**
     * Constructor
     *
     * @param parent Parent widget
     */
    Dist500BaseWidget(QWidget *parent = 0);

    /**
     * Sets the ColorMode property
     *
     * @param colorMode New ColorMode to be used
     */
    void setColorMode(ColorMode colorMode);

    /**
     * Returns the current ColorMode property value
     *
     * @param Active ColorMode
     */
    ColorMode colorMode(void) const;

    /**
     * Sets the PictureMode property
     *
     * @param pictureMode New PictureMode to be applied
     */
    void setPictureMode(PictureMode pictureMode);

    /**
     * Returns the current PictureMode property
     *
     * @return Active PictureMode
     */
    PictureMode pictureMode(void) const;

    /**
     * Returns the current distance factor
     *
     * @return Active distance factor
     */
    int distanceFactor(void) const;

    /**
     * Returns the current amplitude factor
     *
     * @return Active amplitude factor
     */
    int amplitudeFactor(void) const;

    /**
     * Sets the Orientation property
     *
     * @param orientation New Orientation to be set
     */
    void setOrientation(Orientation orientation);

    /**
     * Returns the Orientation property value
     *
     * @return Currently active Orientzation value
     */
    Orientation orientation(void) const;

    /**
     * Returns the current value of the logo flag
     *
     * @param Logo flag (<code>true</code>: show logo if no pic is
     *        available, <code>false</code>: show random values for
     *        unknown data)
     */
    bool showLogo(void);

    bool showPixelValue(void) const;

    unsigned char sensorNo(void) const;

    void setSensorNo(const unsigned char no);

    void clearPictureReceived(void);
    
    void useAlternativeColorSpectrum(bool);
    
    /*
     * recalculates the static array containing alternative color spectrum
     * Pass a pointer to a SpectrumAccessor instance
     */
    static void calculateSpectrum(const SpectrumAccessor&);
    
    /*
     * resets alternative color spectrum to default
     */
    static void resetSpectrum();

public slots:

    /**
     * Sets the distance factor property
     *
     * @param distanceFactor New factor to be applied to distance
     *        pixel values before color mapping
     */
    void setDistanceFactor(int distanceFactor);

    /**
     * Sets the amplitude factor property
     *
     * @param amplitudeFactor New factor to be applied to amplitude
     *        pixel values before color mapping
     */
    void setAmplitudeFactor(int amplitudeFactor);

    /**
     * Resets the internal base values for picture number and timestamp
     * displayed
     */
    void resetBaseValues(void);

    /**
     * Sets the logo flag to a new value
     *
     * @param showLogo New flag (<code>true</code>: show logo if no pic
     *        is available, <code>false</code>: show random values for
     *        unknown data)
     */
    void setShowLogo(bool showLogo);

    void setShowPixelValue(bool showPixelValue);

protected:

    /**
     * Holds the initialization status (<code>true</code>: initialized,
     * <code>false</code> otherwise)
     */
    static bool initialized;

    /**
     * Caches the RGB values for active ColorMode
     */
    static QRgb colorTable[256];

    /**
     * Caches the RGB values for grayscale rendering
     */
    static QRgb grayscaleTable[256];

    /**
     * Caches the RGV values for combined rendering
     */
    static QRgb combinedTable[256][256];

    /**
     * Holds the RGB value for saturated pixels in color-spectrum mode
     */
    static QRgb saturationColorSpectrum;

    /**
     * Holds the RGB value for saturated pixels in grayscale mode
     */
    static QRgb saturationColorGrayscale;

    /**
     * Holds the RGB value for the indicator overlay in color-spectrum
     * mode
     */
    static QRgb indicatorColorSpectrum;

    /**
     * Holds the RGB value for indicator overlays in grayscale mode
     */
    static QRgb indicatorColorGrayscale;

    /**
     * Holds a QPen instance used for rendering of saturated pixels in
     * color-spectrum mode
     */
    static QPen saturationPenSpectrum;

    /**
     * Holds a QPen instance used for rendering of saturated pixels in
     * grayscale mode
     */
    static QPen saturationPenGrayscale;

    /**
     * Holds a QPen instance used for rendering of indicator overlays in
     * color-spectrum mode
     */
    static QPen indicatorPenSpectrum;

    /**
     * Holds a QPen instance used for rendering of indicator overlays in
     * grayscale mode
     */
    static QPen indicatorPenGrayscale;

    /**
     * Points to the currently active RGB cache table
     */
    QRgb *activeTable;

    /**
     * Holds the currently used RGB value assigned to saturated pixels
     */
    QRgb saturationColor;

    /**
     * Holds the currently used RGB value assigned to indicator overlays
     */
    QRgb indicatorColor;

    /**
     * Points to the current active QPen instance used for rendering of
     * saturated pixels
     */
    QPen *saturationPen;

    /**
     * Points to the current active QPen instance used for rendering of
     * indicator overlays
     */
    QPen *indicatorPen;

    /**
     * Holds the current value of the ColorMode property
     */
    ColorMode activeColorMode;

    /**
     * Holds the current value of the PictureMode property
     */
    PictureMode activePictureMode;

    /**
     * Holds the currently active distance value multiplier
     */
    int activeDistanceFactor;

    /**
     * Holds the currently active amplitude value multiplier
     */
    int activeAmplitudeFactor;

    /**
     * Holds the current value of the Orientation property
     */
    Orientation activeOrientation;

    /**
     * Caches the pixel values of the most recently received picture
     */
    unsigned short values[1000];
    
    static void buildAlternativeColorTable();

    /**
     * This method is called when pixel data and/or settings have changed
     * in a way that require re-rendering; this method is abstract,
     * sub-classed need to implement it appropriately
     *
     * @param triggerUpdateEvent Indicates whether an on-screen update is
     *        necessary or not
     */
    virtual void updateImage(bool triggerUpdateEvent = true) = 0;

    /**
     * Cache for pre-multiplied distance values
     */
    unsigned short scaleDistanceValue(unsigned short value) const;

    /**
     * Cache for pre-multiplied amplitude values
     */
    unsigned short scaleAmplitudeValue(unsigned short value) const;

    /**
     * This method is called internally when a Qt requests a size hint.
     * The original sizeHint() method is not used here because it does
     * not take the current Orientation into account
     *
     * @return QSize representing the optimal size
     */
    virtual QSize internalSizeHint(void) const = 0;

    /**
     * Returns the recommended size for the widget. Internally calls
     * internalSizeHint(), transforms the values according to the active
     * orientation and returns the result
     *
     * @return Recommended size
     */
    QSize sizeHint(void) const;

    /**
     * Holds the base timestamp for relative timestamps
     */
    unsigned long long timestampBase;

    /**
     * Holds the base value for relative picture numbers
     */
    unsigned long pictureNumberBase;

    /**
     * Flag indicating the request for base value resets (<code>true</code>:
     * reset flags at next opportunity, <code>false</code> don't)
     */
    bool resetBaseValuesFlag;

    /**
     * Holds the timestamp of the most recent picture received
     */
    unsigned long timestamp;

    /**
     * Holds the picture number of the most recent picture received
     */
    unsigned long long pictureNumber;

    /**
     * Holds the showLogo property value
     */
    bool activeShowLogo;

    /**
     * Indicates whether a first picture has ever been received or not
     */
    bool pictureReceived;

    /**
     * Computes sample values for design mode and no-pic mode (can be either
     * an iris logo or simply random data, according to the showLogo setting)
     */
    void computeSampleValues(void);

    bool activeShowPixelValue;

    unsigned char activeSensorNo;

    virtual void prepareSizeChange(const QSize size);
    
    bool alternativeColorSpectrum;

    static QRgb alternativeColorTable[4096];
    static QRgb alternativeCombinedTable[4096][256];

public slots:

    /**
     * Processes new picture data
     *
     * @param Picture to be processed
     */
    virtual void setPicture(iris::dist500::Picture* picture);

}; // class Dist500BaseWidget

class ImageBufferedDist500BaseWidget : public Dist500BaseWidget {

    Q_OBJECT

protected:

    /**
     * Serves as a cache for the rendered image
     */
    QImage img;

public:

    /**
     * Constructor
     *
     * @param parent Parent widget
     */
    ImageBufferedDist500BaseWidget(QWidget *parent = 0);

};

} // namespace qt

} // namespace iris

#endif // QT_DIST500BASEWIDGET_H
