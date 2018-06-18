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

#ifndef QT_QTSENSORTABLEMODEL_H
#define QT_QTSENSORTABLEMODEL_H

// Qt includes
#include <QAbstractItemModel>
#include <QList>
#include <QMap>
#include <QThread>
#include <QMutex>

// iris includes
#include "QtDist500.h"
#include "../dist500/SensorInfo.h"

namespace iris {

namespace qt {

class SensorInfoCollectionThread;

/**
 * Builds a table model based on a device scan for sensors
 */
class SENSORAPIQT QtSensorTableModel: public QAbstractItemModel {

Q_OBJECT

protected:

    friend class SensorInfoCollectionThread;

    /**
     *
     */
    typedef QMap<QString, QString> IconMap;

    /**
     *
     */
    enum {
        ColumnNameCount = 6
    };

    /**
     *
     */
    static const char* columnNames[ColumnNameCount];

    /**
     *
     */
    iris::drivers::Driver::AddressList list;

    class QtSensorItem {
    public:
        QtSensorItem():sensor(0),gatewayItem(0),index(0),children(),checked(Qt::Unchecked){}
        ~QtSensorItem(){}
        QtDist500* sensor;
        QtSensorItem* gatewayItem;
        int index;
        QList<QtSensorItem*> children;
        Qt::CheckState checked;
    };

    QtSensorItem rootItem;

    /**
     *
     */
    QList<QtSensorItem*> sensorItems;

    QMutex mutex;

    int totalSensors;

    QList<SensorInfoCollectionThread*> threads;

    const bool onlyCompleteFas;

    void collectSelection(const QtSensorItem *item, iris::qt::QtDist500::QtSensorList& list, const bool ignoreSelectionState = false) const;

public slots:

    void threadFinished(void);

public:

    /**
     * Constructor
     *
     * @param parent Parent QObject
     */
    QtSensorTableModel(QObject* parent, const bool onlyCompleteFas = false);
    
    virtual ~QtSensorTableModel();

    void fillTableByBroadcast();
    
    void fillTableByAddresses(iris::drivers::Driver::AddressList& addresses);

    /**
     *
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    /**
     *
     */
    QVariant data(const QModelIndex &index, int role) const;

    /**
     *
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    /**
     *
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    /**
     *
     */
    QtDist500* getSensorForIndex(const QModelIndex& index) const;
    
    void getInfoForAddresses(iris::drivers::Driver::AddressList& addresses);

    void startSensorInfoCollection(void);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

    QModelIndex parent(const QModelIndex &index) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;

    bool setData(const QModelIndex &index, const QVariant &value, int role);

    mutable iris::qt::QtDist500::QtSensorList currentSelection;

    iris::qt::QtDist500::QtSensorList getSelection(void) const;

    iris::qt::QtDist500::QtSensorList getAllSensors(void) const;

    int getTotalSensorCount(void) const;

    void clearSelection(void);

signals:

    void infosComplete(void);

    void selectionChanged(void);

}; // class QtSensorTableModel

} // namespace qt

} // namespace iris

#endif // QT_QTSENSORTABLEMODEL_H
