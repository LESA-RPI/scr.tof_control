// ***************************************************************************
// *    _      _       ____                                 _    ____ ___    *
// *   (_)_ __(_)___  / ___|  ___ _ __  ___  ___  _ __     / \  |  _ \_ _|   *
// *   | | '__| / __| \___ \ / _ \ '_ \/ __|/ _ \| '__|   / _ \ | |_) | |    *
// *   | | |  | \__ \  ___) |  __/ | | \__ \ (_) | |     / ___ \|  __/| |    *
// *   |_|_|  |_|___/ |____/ \___|_| |_|___/\___/|_|    /_/   \_\_|  |___|   *
// *                                                                         *
// *   Copyright (c) 2012 by iris-GmbH, Berlin         All rights reserved   *
// *                                                                         *
// ***************************************************************************

// ---------------------------------------------------------------------------
// Please refer to LICENSE.TXT for more information on copyright and licensing
// terms with respect to this library and its source codes.
// ---------------------------------------------------------------------------

#ifndef QT_QTREPORTSENSORCHOICEDIALOG_H
#define QT_QTREPORTSENSORCHOICEDIALOG_

// Qt forward declarations
class QPushButton;
class QAbstractButton;

// iris includes
#include "iris/qt/QtSensorChoiceDialog.h"

namespace iris {

namespace qt {

class QtReportSensorChoiceDialog : public QtSensorChoiceDialog {

    Q_OBJECT

public:

    explicit QtReportSensorChoiceDialog(QWidget *parent = 0, const SelectionRange& range = SingleRange, 
                    bool offerDriverDialog = false, bool autoSelection = false, bool gatewaysOnly = false, 
                    driverOptionMapType driverOptions = driverOptionMapType(), QString driverToSelect = QString());

    ~QtReportSensorChoiceDialog();
    
    void enableFullReport(void);

    void disableFullReport(void);

    void setDefaultReportDir(QString defaultDir);

private slots:

    void infosComplete(void);

private:

    QPushButton* reportButton;

    int newTimerId;

    bool constructorReady;

    bool fullReport;

    QString defaultReportDir;

    void timerEvent(QTimerEvent* event);

private slots:

    void saveReport(QAbstractButton *button);

};

}

}

#endif // QT_QTREPORTSENSORCHOICEDIALOG_H
