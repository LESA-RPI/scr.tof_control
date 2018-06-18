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

#ifndef IRIS_QT_CONFIGURATIONTABLEMODEL_H
#define IRIS_QT_CONFIGURATIONTABLEMODEL_H

#include <QAbstractItemModel>

// iris includes
#include "../Common.h"
#include "iris/configuration/Configuration.h"

namespace iris {
namespace qt {

class SENSORAPIQT ConfigurationTableModel : public QAbstractItemModel
{
    Q_OBJECT

public:

    explicit ConfigurationTableModel(iris::configuration::Configuration& configuration, QObject *parent = 0);

    enum {
        ColumnNameCount = 6
    };

    typedef enum {paramValue, paramDefaultValue, paramMinValue, paramMaxValue} ParameterValueType;

    static const char* columnNames[ColumnNameCount];

    iris::configuration::Configuration& configuration;

    /*class ParameterGroupItem;

    class Item {
    public:
        Item* parent;
        int index;
        QList<Item*> children;
    };

    class ParameterItem: Item {
    public:
        ParameterGroupItem* parent;
        int index;
        ParameterGroupItem* parent;
    };

    class ParameterGroupItem {
    public:
        ConfigurationGroupItem* parent;
        int index;
        QList<ParameterItem*> children;
    };

    class ConfigurationItem {
    public:
        QList<ParameterGroupItem*> children;
    };

    ConfigurationItem rootItem;*/

    int rowCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;

    int columnCount(const QModelIndex &parent) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;

    QModelIndex parent(const QModelIndex &index) const;

    Qt::ItemFlags flags(const QModelIndex &index) const;

protected:
    QString getParameterTypeName(const iris::configuration::ParameterGroup* group, unsigned short paramId) const;
    QString getParameterValueString(const iris::configuration::ParameterGroup* group, unsigned short groupId, unsigned short paramId, ParameterValueType valueType) const;

};

} // namespace qt
} // namespace iris

#endif // IRIS_QT_CONFIGURATIONTABLEMODEL_H
