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

#ifndef QT_QTDRIVERINFOWIDGET_H
#define QT_QTDRIVERINFOWIDGET_H

// Qt includes
#include <QGroupBox>

// Qt forward declarations
class QWidget;
class QEvent;

// iris includes
#include "../Common.h"

// forward declaration to avoid #include cycle
namespace Ui {
    class QtDriverInfoWidget;
}

namespace iris {

namespace qt {

class SENSORAPIQT QtDriverInfoWidget : public QGroupBox {

    Q_OBJECT

public:

    QtDriverInfoWidget(QWidget* parent = 0);
    ~QtDriverInfoWidget();

public slots:

    void setFilename(const QString& string);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::QtDriverInfoWidget *ui;

}; // clas QtdriverInfowidget

} // namespace qt

} // namespace iris

#endif // QT_QTDRIVERINFOWIDGET_H
