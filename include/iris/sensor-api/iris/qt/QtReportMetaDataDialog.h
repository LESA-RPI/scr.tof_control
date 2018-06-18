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
#ifndef QT_REPORTMETADATADIALOG_H
#define QT_REPORTMETADATADIALOG_H

// Qt includes
#include <QDialog>

class QTranslator;

namespace Ui {
class QtReportMetaDataDialog;
} // namespace Ui

namespace iris {

namespace qt {

class QtReportMetaDataDialog : public QDialog
{
    Q_OBJECT
    
public:

    typedef struct {
        QString customer;
        QString vehicle;
        QString number;
        QString remarks;
        QString user;
        QString date;
    } ReportMetaData;

    /**
     * Constructor
     *
     * @param reportMetaData
     * @param parent Parent QObject
     */
    QtReportMetaDataDialog(ReportMetaData& reportMetaData, QWidget *parent = 0);

    /**
     * Destructor
     */
    ~QtReportMetaDataDialog();
    
private slots:

    /**
     * @brief checkMetaData
     */
    void checkMetaData();

    /**
     * @brief on_buttonBox_accepted
     */
    void on_buttonBox_accepted();

    /**
     * @brief on_buttonBox_rejected
     */
    void on_buttonBox_rejected();

protected:
    QTranslator* translator;

private:

    /**
     * Pointer to IDE-generated UI components
     */
    Ui::QtReportMetaDataDialog *ui;

    /**
     * Meta data reference
     */
    ReportMetaData& reportMetaData;

}; // class QtReportMetaDataDialog

} // namespace qt

} // namespace iris

#endif // QT_REPORTMETADATADIALOG_H
