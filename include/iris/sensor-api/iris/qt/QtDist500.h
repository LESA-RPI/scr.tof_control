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

#ifndef QT_QTDIST500_H
#define QT_QTDIST500_H

// STL includes
#include <string>

// Qt includes
#include <QObject>
//#include <QProgressDialog>
#include <QEvent>

// Qt forward declarations
class QProgressDialog;

// iris includes
#include "iris/drivers/DriverManager.h"
#include "iris/dist500/Dist500.h"
#include "iris/dist500/PictureSink.h"
#include "iris/dist500/CountResultSink.h"
#include "iris/dist500/RegisterValuesSink.h"
#include "iris/dist500/DoorStateSink.h"
#include "QtDist500MetaTypes.h"
#include "iris/synchronization/Mutex.h"

namespace iris {

namespace qt {

/**
 * Qt adapter class for Dist500
 */
class SENSORAPIQT QtDist500: public QObject, public iris::dist500::Dist500, protected iris::dist500::PictureSink,
        protected iris::dist500::CountResultSink, protected iris::dist500::RegisterValuesSink, protected iris::dist500::DoorStateSink {

Q_OBJECT

protected:

    /**
     *
     */
    QWidget* par;

    /**
     *
     */
    QProgressDialog *pd;

    /**
     *
     */
    bool picLimited;

    /**
     *
     */
    bool activeShowProgress;

    /**
     *
     */
    unsigned long long progressValue;

    /**
     *
     */
    static void _installationModeStatusCallback(void* userData, bool running);

    /**
     *
     */
    static void _installationModeProgressCallback(void* userData,
            long pictureNumber, long maxPics, unsigned long long elapsedTime,
            unsigned long long maxTime);

    /**
     *
     */
    void installationModeStatusCallback(bool running);

    /**
     *
     */
    void installationModeProgressCallback(long pictureNumber, long maxPics,
            unsigned long long elapsedTime, unsigned long long maxTime);

    /**
     *
     */
    bool eventFilter(QObject *obj, QEvent *event);

    /**
     *
     */
    static void _updateCallback(void* userData, unsigned int step,
            unsigned int totalSteps, double stepPercentage,
            double totalPercentage);

    /**
     *
     */
    void updateCallback(unsigned int step, unsigned int totalSteps,
            double stepPercentage, double totalPercentage);

    unsigned int step;

    unsigned int totalSteps;

    double stepPercentage;

    double totalPercentage;

    static iris::synchronization::Mutex cacheMutex;

    typedef std::map<iris::drivers::Sensor*, QtDist500*> BaseToQtSensorMap;

    static BaseToQtSensorMap qtSensorCache;// stores QtDist500 pointers by their Sensor pointers; accessed by QtDist500::getInstance()

    static void _transferConfigurationCallback(void* userData, iris::uip::ulong index, iris::uip::ulong total, iris::uip::ushort groupId, iris::uip::ushort paramId);

    void transferConfigurationCallback(iris::uip::ulong index, iris::uip::ulong total, iris::uip::ushort groupId, iris::uip::ushort paramId);

    bool convertQStringToUtf8StdString(const QString& qHexfileName, std::string& stdFileName);

//public:

    /**
     * Constructor
     *
     * @param parent Parent widget
     * @param sensor Sensor instance from driver
     */
    explicit QtDist500(QWidget *parent, iris::drivers::Sensor& sensor);

    /**
     * Destructor
     */
    virtual ~QtDist500();

public:

    /**
     * @brief getInstance Creates an instance and stores it in static qtSensorCache
     * @param sensor
     * @return 
     */
    static QtDist500& getInstance(iris::drivers::Sensor& sensor);
    
    /**
     * @brief QtDist500::clearSensorCache Clears static qtSensorCache
     */
    static void clearSensorCache();

    /**
     * Starts the installation mode
     *
     * @param type Type of installation mode
     * @param maxPictures Optional picture limit (0: unlimited)
     * @param maxTime Optional time limit in ms (0: unlimited)
     */
    void startInstallationMode(InstallationModeType type, unsigned long maxPictures,
            unsigned long long maxTime);

    /**
     * Stops the installation mode
     */
    void stopInstallationMode(void);

    /**
     *
     */
    bool showProgress(void) const;

    /**
     * Updates the application firmware part from the given .LDR file
     *
     * @param hexfileName Filename of the .LDR file containing the firmware
     * @param userData User-defined additional parameter for callback
     * @param updateCallback Callback function for progress updates
     *
     * @return Operation result
     */
    bool performApplicationFirmwareUpdate(const QString& hexfileName);

    bool performApplicationFirmwareUpdate(char* data, unsigned long size,
             const QString& hexfileName, const QString& timestamp);

    /**
     * Updates the bootloader firmware part from the given .LDR file
     *
     * @param hexfileName Filename of the .LDR file containing the firmware
     * @param userData User-defined additional parameter for callback
     * @param updateCallback Callback function for progress updates
     *
     * @return Operation result
     */
    bool performBootloaderFirmwareUpdate(const QString& hexfileName);

    bool performBootloaderFirmwareUpdate(char* data, unsigned long size,
             const QString& hexfileName, const QString& timestamp);

    /**
     * Updates the application firmware info block according to the given .LDR file
     *
     * @param hexfileName Filename of the .LDR file containing the firmware
     * @param userData User-defined additional parameter for callback
     * @param updateCallback Callback function for progress updates
     *
     * @return Operation result
     */
    bool writeApplicationFirmwareInfoBlock(const QString& hexfileName);

    /**
     * Updates the bootloader firmware info block according to the given .LDR file
     *
     * @param hexfileName Filename of the .LDR file containing the firmware
     * @param userData User-defined additional parameter for callback
     * @param updateCallback Callback function for progress updates
     *
     * @return Operation result
     */
    bool writeBootloaderFirmwareInfoBlock(const QString& hexfileName);

    /**
     * Loads the primary or secondary FPGA bitfile (firmware)
     *
     * @param bitfileName Filename of the .BIT file containing the firmware
     * @param primary <code>true</code> if primary image is to be loaded,
     *        <code>false</code> for secondary image
     * @param userData User-defined additional parameter for callback
     * @param updateCallback Callback function for progress updates
     *
     * @return Operation result
     */
    bool loadFpgaImage(const QString& bitfileName, bool primary);

    bool loadFpgaImage(const unsigned char* data, const unsigned int size, bool primary);

    bool performFpgaImageVerification(const QString& hexfileName, bool primary);

    bool performFpgaImageVerification(const unsigned char* data, const unsigned int size, bool primary);

#if 0

    /**
     * Writes an initial configuration data block with given MAC and serial
     *
     * @param serial Serial number
     * @param mac MAC address
     * @param pcbSerial Serial number of base PCB board
     * @param userData User-defined additional parameter for callback
     * @param updateCallback Callback function for progress updates
     *
     * @return Operation result
     *
     * @note IP address will be 10.3.x.y where x and y are the last two bytes
     *       of the MAc address. Type name will be DIST500.M3. All other fields
     *       will receive default values.
     */
    bool writeInitialM3ConfigurationData(const QString& serial,
            const iris::dist500::Dist500::MacAddress& mac,
            const QString& pcbSerial);

#endif

    /**
     * Typedef for a list of QtDist500 instances
     */
    typedef QList<QtDist500*> QtSensorList;

    /**
     * Configures a sensor as master and optionally one or more sensors as slaves to
     * this master; configuration includes the function area address and the door
     * number
     *
     * @param slaves (Possibly empty) list of slaves
     *
     * @return Operation result
     */
    bool configureSensorGroup(const QtSensorList& slaves, const iris::configuration::CommunicationGroup::IpAddress& ipAddr,
                              const iris::configuration::CommunicationGroup::IpAddress& netMask,
                              const iris::configuration::CommunicationGroup::IpAddress& gwAddr, const unsigned short port,
                              const iris::configuration::CommunicationGroup::IpAddress& sntp1Addr, const iris::configuration::CommunicationGroup::IpAddress& sntp2Addr,
                              iris::dist500::FirmwareController::ConfigurationInterceptor& interceptor);

    bool configureStandaloneSensor(const iris::configuration::CommunicationGroup::IpAddress& ipAddr,
                                   const iris::configuration::CommunicationGroup::IpAddress& netMask,
                                   const iris::configuration::CommunicationGroup::IpAddress& gwAddr, const unsigned short port,
                                   const iris::configuration::CommunicationGroup::IpAddress& sntp1Addr, const iris::configuration::CommunicationGroup::IpAddress& sntp2Addr,
                                   iris::dist500::FirmwareController::ConfigurationInterceptor& interceptor);

    bool performBootloaderFirmwareVerification(const QString& hexfileName);

    bool performBootloaderFirmwareVerification(char* data, unsigned long size);

    bool performApplicationFirmwareVerification(const QString& hexfileName);

    bool performApplicationFirmwareVerification(char* data, unsigned long size);

    iris::dist500::SENSOR_RESULT readConfiguration(iris::configuration::Dist500Configuration &config, ConfigurationMismatches &mismatches);

    iris::dist500::SENSOR_RESULT readConfiguration(iris::configuration::Dist500Configuration &configs);

    iris::dist500::SENSOR_RESULT writeConfiguration(iris::configuration::Dist500Configuration &config);

signals:

    /**
     * This signal is emitted whenever a new picture comes in
     *
     * @param picture Picture instance
     * @param pictureIndex 0-based index of the picture if the total number of
     *        pictures is known, 0 otherwise
     * @param pictureIndexCount Total number of picture (0 if unknown)
     */
    void newPicture(iris::dist500::Picture* picture, unsigned long pictureIndex, unsigned long pictureIndexCount);

    /**
     * This signal is emitted whenever a new count result comes in
     *
     * @param countResult CountResult instance
     * @param countIndex 0-based index of the result if the total number of
     *        results is known, 0 otherwise
     * @param countIndexCount Total number of results (0 if unknown)
     */
    void newCountResult(iris::dist500::CountResult countResult, unsigned long countIndex, unsigned long countIndexCount);

    /**
     * This signal is emitted whenever a new register values come in
     *
     * @param values ReigsterValues instance
     * @param registerValuesIndex 0-based index of the values if the total number of
     *        values is known, 0 otherwise
     * @param registerValuesIndexCount Total number of values (0 if unknown)
     */
    void newRegisterValues(iris::dist500::RegisterValues values, unsigned long registerValuesIndex, unsigned long registerValuesIndexCount);

    /**
     * This signal is emitted whenever a new door state comes in
     *
     * @param state DoorState instance
     * @param stateIndex 0-based index of the state if the total number of
     *        states is known, 0 otherwise
     * @param stateIndexCount Total number of states (0 if unknown)
     */
    void newDoorState(iris::dist500::DoorState state, unsigned long stateIndex, unsigned long stateIndexCount);

    /**
     * This signal is emitted when the installation mode is started
     */
    void started();

    /**
     * This signal is emitted when the installation mode is cancelled
     */
    void cancelled();

    /**
     * This signal is emitted when the installation mode is stopped
     */
    void stopped();

    /**
     * This signal is emitted when the running states changes
     *
     * @param running <code>true</code> if installation mode is
     *        running, <code>false</code> otherwise
     */
    void instModeStatusChanged(bool running);

    /**
     *
     */
    void instModeProgressChanged(long pictureNumber, long maxPics,
            unsigned long long elapsedTime, unsigned long long maxTime);

    void transferConfigurationProgressChanged(iris::uip::ulong index, iris::uip::ulong total, iris::uip::ushort groupId, iris::uip::ushort paramId);

    /**
     *
     */
    void updateProgressChanged(unsigned int step, unsigned int totalSteps,
            double stepPercentage, double totalPercentage);

public slots:

    /**
     * Controls whether a progress dialog is shown or not
     *
     * @param
     */
    void setShowProgress(bool showProgress);

protected:

    void processNewPicture(iris::dist500::Picture* picture,
                unsigned long pictureIndex, unsigned long pictureIndexCount);

    void processNewCountResult(iris::dist500::CountResult* result,
                unsigned long countIndex, unsigned long countIndexCount);

    void processNewRegisterValues(iris::dist500::RegisterValues* values,
                unsigned long registerValuesIndex, unsigned long registerValuesIndexCount);

    void processNewDoorState(iris::dist500::DoorState* state,
                unsigned long stateIndex, unsigned long stateIndexCount);

    class ProgressDialogEvent: public QEvent {
    public:
        const QString &labelText;
        const QString &cancelButtonText;
        int minimum;
        int maximum;
        QWidget *parent;
        Qt::WindowFlags flags;
        QString windowTitle;
        bool noCancelButton;
        ProgressDialogEvent(const QString &labelText, const QString &cancelButtonText,
                            int minimum, int maximum, QWidget *parent = 0, Qt::WindowFlags flags = 0);
    };

}; // class Dist500

} // namespace qt

} // namespace iris

#endif // QT_QTDIST500_H
