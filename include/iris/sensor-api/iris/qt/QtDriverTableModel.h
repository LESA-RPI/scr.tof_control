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

#ifndef QT_QTDRIVERTABLEMODEL_H
#define QT_QTDRIVERTABLEMODEL_H

// Qt includes
#include <QAbstractListModel>
#include <QList>
#include <QMap>

// iris includes
#include "QtDist500MetaTypes.h"

// iris forward declarations
namespace iris {
    namespace drivers {
        class Driver;
    }
}

namespace iris {

namespace qt {

/**
 * Builds a table model based on a device scan for sensors
 */
class SENSORAPIQT QtDriverTableModel: public QAbstractListModel {

Q_OBJECT

protected:

    /**
     *
     */
    enum {
        ColumnNameCount = 5
    };

    /**
     *
     */
    static const char* columnNames[ColumnNameCount];

    /**
     *
     */
    QList<iris::drivers::Driver*> drivers;

public:

    /**
     * Constructor
     *
     * @param parent Parent QObject
     */
    QtDriverTableModel(QObject* parent);

    /**
     *
     */
    int rowCount(const QModelIndex &parent) const;

    /**
     *
     */
    QVariant data(const QModelIndex &index, int role) const;

    /**
     *
     */
    int columnCount(const QModelIndex &parent) const;

    /**
     *
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    iris::drivers::Driver* getDriverAt(int index);

}; // class QtDriverTableModel

} // namespace qt

} // namespace iris

#endif // QT_QTDRIVERTABLEMODEL_H
