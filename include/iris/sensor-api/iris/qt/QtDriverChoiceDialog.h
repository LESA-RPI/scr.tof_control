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

#ifndef QT_QTDRIVERCHOICEDIALOG_H
#define QT_QTDRIVERCHOICEDIALOG_H

// Qt includes
#include <QDialog>


// Qt forward declarations
class QItemSelection;
class QPushButton;
class QTranslator;

// forward declaration to avoid #include cycle
namespace Ui {
    class QtDriverChoiceDialog;
}

// iris includes
#include "QtDist500MetaTypes.h"

// iris forward declarations
namespace iris {
    namespace qt {
        class QtDriverTableModel;
    }
}
//#include "QtDriverTableModel.h"


namespace iris {

namespace qt {

class SENSORAPIQT QtDriverChoiceDialog : public QDialog {

    Q_OBJECT

public:
    explicit QtDriverChoiceDialog(QWidget *parent = 0);
    ~QtDriverChoiceDialog();
    bool hasAnyChanges(void);

private:

    Ui::QtDriverChoiceDialog *ui;

    QTranslator* translator;

    /**
     * Table model instance
     */
    QtDriverTableModel* tableModel;

    QPushButton* startupButton;
    QPushButton* shutdownButton;
    QPushButton* optionsButton;
    QPushButton* loadButton;
    QPushButton* unloadButton;

    iris::drivers::Driver* selectedDriver;
    bool anyChanges;

    private slots:

    void loadButton_clicked(void);
    void unloadButton_clicked(void);
    void startupButton_clicked(void);
    void shutdownButton_clicked(void);
    void optionsButton_clicked(void);

    /**
     * Slot for selection change event of the sensor table
     *
     * @param selected Newly selected items
     * @param deselected Newly deselected items
     */
    void driverTableSelectionChanged(const QItemSelection & selected,
            const QItemSelection & deselected);

}; // class QtDriverChoiceDialog

} // namespace qt

} // namespace iris

#endif // QT_QTDRIVERCHOICEDIALOG_H
