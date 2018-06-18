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

#ifndef DIST500OPENGLWIDGET_H_
#define DIST500OPENGLWIDGET_H_

// iris includes
#include "Dist500BaseWidget.h"

// Qt includes
#include <QtOpenGL>

class QKeyEvent;
class QMouseEvent;

namespace iris {

namespace qt {


/***************************************************************************//**
*   @brief
*******************************************************************************/

const short SENSOR_WIDTH = 25;                              ///< pixels in x direction
const short SENSOR_HEIGHT = 20;                             ///< pixels in y direction
const short SENSOR_RANGE = 4096;                            ///< bit range of sensor (2^12 Bit)
const short SENSOR_PIXEL = 500;                             ///< pixels of sensor image
const float SENSOR_DEPTHMAX = (float)5.0;                   ///< maximum depth range (Marec for 30MHz)
const float SENSOR_CHIPWIDTH = (float)2.5;                  ///< width of sensor chip [mm]
const float SENSOR_CHIPHEIGHT = (float)2.0;                 ///< height of sensor chip [mm]
const float SENSOR_FOCALLENGTH = (float)2.66;               ///< focal length of sensor chip [mm]
const short SENSOR_HALF_WIDTH = 12;                         ///< pixels in x direction
const short SENSOR_HALF_HEIGHT = 10;                        ///< pixels in y direction
const float SENSOR_NORM_X = (float)0.9398;                  ///< norm value for x coordinate calculation
const float SENSOR_NORM_Y = (float)0.7518;                  ///< norm value for y coordinate calculation
const float SENSOR_DIGIT_TO_MM = (float)1.2207;             ///< conversation from digit to mm (Marec for 30MHz)
const float SENSOR_MM_TO_DIGIT = (float)0.8192;             ///< conversation from mm to digit (Marec for 30MHz)
const float SENSOR_NORM_WIDTH = 1/(float)SENSOR_WIDTH;      ///< normalized sensor chip width
const float SENSOR_NORM_HEIGHT = 1/(float)SENSOR_HEIGHT;    ///< normalized sensor chip height
const float SENSOR_NORM_PIXEL = 1/(float)SENSOR_PIXEL;      ///< normalized sensor chip pixel

/***************************************************************************//**
*   @brief
*******************************************************************************/

typedef struct {
    GLfloat r, g, b;
} VERTEX_RGB;

typedef struct {
    GLfloat x, y, z;
} VERTEX_XYZ;

typedef struct {
    GLfloat radius;
    GLfloat x, y, z;
    GLfloat r, g, b;
} SPHERE_3D;

class MatrixSceneWidget;

/***************************************************************************//**
*   @brief
*******************************************************************************/

class SENSORAPIQT Dist500OpenGlWidget: public Dist500BaseWidget {

    Q_OBJECT

    public:

        /**
         *  Defines the supported vertex modes.
         */
        enum VERTEX_MODE {
            Points,
            Lines
        };

        /**
         *  Defines the supported view modes.
         */
        enum VIEW_MODE {
            Top,
            Front,
            Back,
            Right,
            Left,
            User
        };

        Q_ENUMS(VERTEX_MODE VIEW_MODE)

    protected:

        Q_PROPERTY(int xRotation READ xRotation WRITE setXRotation)
        Q_PROPERTY(int yRotation READ yRotation WRITE setYRotation)
        Q_PROPERTY(int zRotation READ zRotation WRITE setZRotation)
        Q_PROPERTY(int vertexSize READ vertexSize WRITE setVertexSize)
        Q_PROPERTY(VERTEX_MODE vertexMode READ vertexMode WRITE setVertexMode)
        Q_PROPERTY(VIEW_MODE viewMode READ viewMode WRITE setViewMode)
        Q_PROPERTY(double scaleFactor READ scaleFactor WRITE setScaleFactor)

    public slots:

        int xRotation(void) const;
        int yRotation(void) const;
        int zRotation(void) const;
        int vertexSize(void) const;
        VERTEX_MODE vertexMode(void) const;
        VIEW_MODE viewMode(void) const;
        double scaleFactor(void) const;

        void setXRotation(const int angle);
        void setYRotation(const int angle);
        void setZRotation(const int angle);
        void setVertexSize(const int size);
        void setVertexMode(const VERTEX_MODE mode);
        void setViewMode(const VIEW_MODE mode);
        void setScaleFactor(const double scale);

        void resetScaleFactor(void);
        void zoomIn(void);
        void zoomOut(void);
        void zoomIn(const unsigned steps);
        void zoomOut(const unsigned steps);
        void zoomRelative(const signed steps);

    protected:

        MatrixSceneWidget * sceneWidget;
        QBoxLayout * sceneLayout;

    public:

        Dist500OpenGlWidget(QWidget * parent = 0);
        ~Dist500OpenGlWidget();

            /** This method is called when pixel data and/or settings have changed in a way
                that require re-rendering. triggerUpdateEvent indicates whether an on-screen
                update is necessary or not. */
        virtual void updateImage(bool triggerUpdateEvent = true);
            /** Returns a size hint (in normal 0 degrees orientation). */
        virtual QSize internalSizeHint(void) const;
            /** Saves the image content in a image file. */
        void saveScene(const QString filename, const QString format);
            /** Reset image content and reset parameter. */
        void reset(void);

    private:

        unsigned short sceneValues[500];
        QColor sceneColors[500];

}; // class Dist500OpenGlWidget

/***************************************************************************//**
*   @brief
*******************************************************************************/

class SENSORAPIQT MatrixSceneWidget: public QGLWidget {

    Q_OBJECT

    Q_ENUMS(iris::qt::Dist500OpenGlWidget::VERTEX_MODE iris::qt::Dist500OpenGlWidget::VIEW_MODE)

    Q_PROPERTY(int xRotation READ xRotation WRITE setXRotation)
    Q_PROPERTY(int yRotation READ yRotation WRITE setYRotation)
    Q_PROPERTY(int zRotation READ zRotation WRITE setZRotation)
    Q_PROPERTY(int vertexSize READ vertexSize WRITE setVertexSize)
    Q_PROPERTY(iris::qt::Dist500OpenGlWidget::VERTEX_MODE vertexMode READ vertexMode WRITE setVertexMode)
    Q_PROPERTY(iris::qt::Dist500OpenGlWidget::VIEW_MODE viewMode READ viewMode WRITE setViewMode)
    Q_PROPERTY(double scaleFactor READ scaleFactor WRITE setScaleFactor)

    public:

        MatrixSceneWidget(QWidget * parent = 0);
        ~MatrixSceneWidget();

        void updateScene(const unsigned short * values, const QColor * colors);
        void saveScene(const QString filename, const QString format);
        void reset(void);

            /** Scene viewed from above. */
        void setTopView(void);
            /** Scene viewed from the front. */
        void setFrontView(void);
            /** Scene viewed from back. */
        void setBackView(void);
            /** Scene viewed from right. */
        void setRightView(void);
            /** Scene viewed from left. */
        void setLeftView(void);

        void setPainterActive(const bool paint);
        void set2DCursorPosistion(const QPoint position);
        void setSphere(const SPHERE_3D sphere);
        void clearSphereVector(void);

    public slots:

        int xRotation(void) const;
        int yRotation(void) const;
        int zRotation(void) const;
        int vertexSize(void) const;
        iris::qt::Dist500OpenGlWidget::VERTEX_MODE vertexMode(void) const;
        iris::qt::Dist500OpenGlWidget::VIEW_MODE viewMode(void) const;
        double scaleFactor(void) const;

        void setXRotation(const int angle);
        void setYRotation(const int angle);
        void setZRotation(const int angle);
        void setVertexSize(const int size);
        void setVertexMode(const iris::qt::Dist500OpenGlWidget::VERTEX_MODE mode);
        void setViewMode(const iris::qt::Dist500OpenGlWidget::VIEW_MODE mode);
        void setScaleFactor(const double scale);

        void resetScaleFactor(void);
        void zoomIn(void);
        void zoomOut(void);
        void zoomIn(const unsigned steps);
        void zoomOut(const unsigned steps);
        void zoomRelative(const signed steps);

    signals:

        void xRotationChanged(int angle);
        void yRotationChanged(int angle);
        void zRotationChanged(int angle);

    protected:

            /** Callback main routine. */
        void paintGL(void);
            /** Register keyboard events. */
        void keyPressEvent(QKeyEvent * event);
            /** Register mouse press events. */
        void mousePressEvent(QMouseEvent * event);
            /** Register mouse move events. */
        void mouseMoveEvent(QMouseEvent * event);
            /** Register mouse wheel scroll events. */
        void wheelEvent(QWheelEvent * event);

    private:

            /** Universal vertex for color. */
        VERTEX_RGB vertexRGB;
            /** Universal vertex for coordinates. */
        VERTEX_XYZ vertexXYZ;

            /** Image data for colors. */
        VERTEX_RGB imageRGB[SENSOR_HEIGHT*SENSOR_WIDTH];
            /** Image data for coordinates. */
        VERTEX_XYZ imageXYZ[SENSOR_HEIGHT*SENSOR_WIDTH];

            /** Holds spheres which can be placed on window. */
        std::vector<SPHERE_3D> sphereVector;

            /** Content scaling factor. */
        double scaleContent;
            /** Rotation angle x. */
        double angleRotationX;
            /** Rotation angle y. */
        double angleRotationY;
            /** Rotation angle z. */
        double angleRotationZ;
            /** Vertical offset angle. */
        double angleVertical;
            /** Horizontal offset angle. */
        double angleHorizontal;
            /** Offset angle of rotation of scene. */
        double anglePitch;
            /** Offset angle of rotation to scene. */
        double angleYaw;

            /** 3D mouse position. */
        QPoint posMouse;
            /** 2D cursor position. */
        QPoint posCursor;

            /** Mode for view (perspective) mode. */
        int modeView;
            /** Mode for vertex representation. */
        int modeVertex;
            /** Size for vertex representation. */
        int sizeVertex;
            /** Flag to set content. */
        bool paint;

            /** Draw scene using sensor data. */
        void drawScene(void);
            /** Defines the vertex placed at position x,y. */
        void drawVertex(const int x, const int y);
            /** Defines the sphere placed at position x,y,z. */
        void drawSphere(const SPHERE_3D sphere);
            /** Draw spheres to image. */
        void drawSpheres(void);

}; // class MatrixSceneWidget

} // namespace qt

} // namespace iris

#endif // DIST500OPENGLWIDGET_H
