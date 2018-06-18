#ifndef SENSORINFOCOLLECTIONTHREAD_H
#define SENSORINFOCOLLECTIONTHREAD_H

// Qt includes
#include <QThread>

// iris includes
#include "iris/qt/QtSensorTableModel.h"

namespace iris {

namespace qt {

class SensorInfoCollectionThread: public QThread {

    Q_OBJECT

protected:
    QtSensorTableModel::QtSensorItem* si;
    const QModelIndex index;
    QtSensorTableModel* model;

public:
    SensorInfoCollectionThread(QtSensorTableModel* model, const QModelIndex& index);
    void run(void);
signals:
    void refreshNeeded(const QModelIndex& from, const QModelIndex& to);
};

} // namespace qt

} // namespace iris

#endif // SENSORINFOCOLLECTIONTHREAD_H
