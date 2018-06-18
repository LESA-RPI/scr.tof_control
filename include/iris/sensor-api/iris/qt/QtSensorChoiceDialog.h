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

#ifndef QT_QTSENSORCHOICEDIALOG_H
#define QT_QTSENSORCHOICEDIALOG_H

// Qt includes
#include <QDialog>
#include <QMap>

// iris includes
#include "iris/drivers/Driver.h"
#include "iris/qt/QtDist500.h"

// iris forward declarations
namespace iris { 
    namespace qt {
        class QtSensorTableModel;
    }
}

// Qt forward declarations
class QTranslator;
class QCompleter;
class QSortFilterProxyModel;
class QDialogButtonBox;
class QItemSelection;
class QModelIndex;

namespace Ui {
class QtSensorChoiceDialog;
} // namespace Ui

Q_DECLARE_METATYPE(iris::drivers::Driver*)

namespace iris {

namespace qt {

/**
 * Implements a dialog presenting a list of all sensors found during the
 * device scan; the use can then chose a sensor to work with
 */

class SENSORAPIQT QtSensorChoiceDialog: public QDialog {

Q_OBJECT

public:

    class SENSORAPIQT SelectionRange {

    protected:

        friend class QtSensorChoiceDialog;

        /**
         * Minimum number of sensors to be selected by the user
         */
        unsigned int minSelection;

        /**
         * Maximum number of sensors to be selected by the user
         */
        unsigned int maxSelection;

    public:

        /**
         * Constructor
         *
         * @param minSelection Minimum number of sensors to be selected by the user
         * @param maxSelection Maximum number of sensors to be selected by the user
         */
        SelectionRange(unsigned int minSelection, unsigned int maxSelection = UINT_MAX);

    };

protected:

    /**
     * Pointer to IDE-generated UI components
     */
    Ui::QtSensorChoiceDialog *ui;

    QTranslator* translator;

    /**
     * Catches and processes language change events
     */
    void changeEvent(QEvent *e);

    /**
     * Selection range
     */
    SelectionRange range;

    /**
     * Auto selection flag
     */
    bool autoSelection;

    /**
     * Timer event handler
     */
    void timerEvent(QTimerEvent* event);

    bool gatewaysOnly;

    bool autoSelectionSuccess;

    int timerId;
    
    static const QVector<std::string> test123;
    
    static const QVector<std::string> supportedDriverOptionsIcef;
    static const QVector<std::string> supportedDriverOptionsUdp;
    static const QVector<std::string> supportedDriverOptionsCan;
    static const QVector<std::string> supportedDriverOptionsSerial;
    static const QVector<std::string> supportedDriverOptionsAllProtocols;
    QMap<QString, const QVector<std::string>*> supportedDriverOptionsByDriverName;
    QVector<std::string> localNicIps;// local NIC Ip-Addresses for auto completion

    QMap<QString, QCompleter*> driverOptionCompleter;
    QCompleter* completerLocalNicIp;
    QCompleter* completerSenderUip;
    QCompleter* completerTrueFalse;
    
    unsigned int lastScannedIndex;
    
    bool scanRunning;
    
    bool collectingInfos;
    
    iris::drivers::Driver::AddressList scanResultAddresses;
    
public:
    
    typedef QMap<QString, QString> driverOptionMapType;
    
    void getSupportedDriverOptions(const QString& driverName, QVector<std::string>& supportedOptions);
    
    static void getSupportedDriverOptionsCombined(QVector<std::string>& supportedOptions);
    
    void getDriverOptions(driverOptionMapType& destinationMap) const {destinationMap = driverOptionMap;}
    
    void setDriverOptions(const driverOptionMapType& sourceMap) {driverOptionMap = sourceMap;}
    
    void selectDriverByName(const QString& driverName);
    
    QString getSelectedDriverName() const;
    
protected:
    void closeEvent(QCloseEvent* event);

    void reject();

    driverOptionMapType driverOptionMap;
    
    void initializeDriverOptions();
    
    void applyDriverOptions();
    
    void refreshDriverOptionValidation();
    
    void getDriverOptionsForCurrentDriver(driverOptionMapType& outputMap);

public:

    static const SelectionRange SingleRange;

    static const SelectionRange OneOrMoreRange;

    /**
     * Constructor
     *
     * @param parent Parent QObject
     * @param minSelection Minimum number of sensors to be selected by the user
     * @param maxSelection Maximum number of sensors to be selected by the user
     * @param offerDriverDialog Flag indicating whether a driver administration
     *        dialog can be opened (<code>true</code>) or not (<code>false</code>)
     * @param autoSelection Auto selection flag
     * @param driverOptions A map with driver options. Useful to load these from persistent user settings
     * @param driverToSelect Name of the driver to select in the driver combo box.
     */
    QtSensorChoiceDialog(QWidget *parent = 0, const SelectionRange& range = SingleRange, 
                bool offerDriverDialog = false, bool autoSelection = false, bool gatewaysOnly = false,
                driverOptionMapType driverOptions = driverOptionMapType(), QString driverToSelect = QString());

    /**
     * Destructor
     */
    ~QtSensorChoiceDialog();

    /**
     * Table model instance
     */
    QtSensorTableModel *tableModel;

    QSortFilterProxyModel* proxyModel;

    /**
     * Returns the first selected sensor
     */
    iris::qt::QtDist500* getFirstChosenSensor(void);

    /**
     * Returns the list of selected sensors
     */
    iris::qt::QtDist500::QtSensorList getChosenSensors(void) const;

    /**
     * Set the sensor choice table caption
     */
    void setSensorChoiceCaption(QString caption);

    /**
     * Returns the Driver instance that is currently selected in the
     * driver combobox
     *
     * @return Driver instance pointer
     */
    iris::drivers::Driver* getSelectedDriver(void);
    
private:

    void safelyAbortScans();
    
public slots:

    int exec();

protected slots:

    void recreateModel();

    /**
     * Slot for click event of the refresh button
     */
    void on_refreshButton_clicked();

    /**
     * Slot for selection change event of the sensor table
     *
     * @param selected Newly selected items
     * @param deselected Newly deselected items
     */
    void sensorTableSelectionChanged(const QItemSelection & selected,
            const QItemSelection & deselected);

    void sensorTableNewSelection(void);

    void setScanGuiVisibility(bool);
    void on_pushButtonScanToggle_clicked();
    
    void resizeToContents();
    
    void startScan();
    
    void nextScan();
    void on_pushButtonScanStartStop_clicked(bool checked);
    
    void checkScanRange();
    void on_lineEditScanFrom_textChanged(const QString &arg1);
    void on_lineEditScanTo_textChanged(const QString &arg1);
    
    void on_lineEditScanTo_returnPressed();
    void stopScan();
    
    void updateSensorCount();

    /**
     * Slot for double click event
     * (simulates click of OK button, if enabled)
     */
    void sensorTableDoubleClicked(const QModelIndex& index);

    /**
     * Slot for click event of drivers... button
     */
    void driversButton_clicked(void);

    virtual void infosComplete(void);

    void driverChanged(int index);

    void refreshDriverComboBox(void);
    
    void refreshDriverOptionComboBox(void);
    
    void on_lineEditDriverOptionValue_textEdited(const QString & newValue);
    
    void on_lineEditDriverOptionValue_textChanged(const QString & newValue) {on_lineEditDriverOptionValue_textEdited(newValue);}
    
    void on_lineEditDriverOptionValue_returnPressed();

    void on_comboBoxDriverOptionName_currentIndexChanged(int index);

    QDialogButtonBox* getButtonBox(void);

}; // class SensorChoiceDialog

} // namespace qt

} // namespace iris

#endif // QT_SENSORCHOICEDIALOG_H
