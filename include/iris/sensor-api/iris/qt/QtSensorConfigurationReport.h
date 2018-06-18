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

#ifndef QT_QTSENSORCONFIGURATIONREPORT_H
#define QT_QTSENSORCONFIGURATIONREPORT_H

// Qt includes
#include <QPainter>
#include <QPrinter>
#include <QRect>
#include <QObject>

// iris includes
#include "iris/qt/QtDist500.h"
#include "iris/qt/QtReportMetaDataDialog.h"

// iris forward declarations
namespace iris {
    namespace drivers {
        class Driver;
    }
}

namespace iris {

namespace qt {

// iris forward declarations
class QtSensorTableModel;

class QtSensorConfigurationReport: public QObject {

    Q_OBJECT

protected:

    QPrinter printer;

    QPainter painter;

    iris::qt::QtDist500::QtSensorList sensors;

    const iris::qt::QtSensorTableModel& sensorTableModel;

    const iris::drivers::Driver* driver;

    const QFont sensorFont;

    const QFont groupFont;

    const QFont paramFont;

    const QFont headerAndFooterFont;

    const QFont headerCaptionFont;

    int mmPixels;

    int fontHeight;

    int fontAscent;

    int yPos;

    QRect pageRect;

    int pageNumber;

    QString dataCustomer;
    QString dataVehicle;
    QString dataNumber;
    QString dataUser;
    QString dataDate;

    void addSensorHeadline(iris::qt::QtDist500* dist500);

    void addGroupHeadline(const QString groupId, const QString groupName);

    void addParameterLine(const QStringList &columns);

    void ensureSpace(int height);

    void addSensorFailure(iris::qt::QtDist500* dist500);

    void addSensorConfiguration(iris::qt::QtDist500* dist500,
            iris::configuration::Dist500Configuration& configuration,
            bool fullReport);

    void selectFont(const QFont& font);

    void addSensorSummary(void);

    void addContextInfo(const QtReportMetaDataDialog::ReportMetaData& metaData);

    void drawText(const int leftMm, const QString& text, const bool advanceYPos = true);

    static const int paramColLeftMm[6];

    static const int summaryColLeftMm[4];

    static const int shortReportParamCount = 47;

    static const unsigned int shortReportParams[shortReportParamCount];

    static bool anyParamInShortReport(int groupId);

    static bool paramInShortReport(int groupId, int paramId);

    void addHeaderAndFooter(void);

public:

    QtSensorConfigurationReport(const iris::qt::QtSensorTableModel *sensorTableModel,
            const iris::drivers::Driver *driver, QObject* parent = 0);

    ~QtSensorConfigurationReport();

    bool createDocument(const QString &fileName, const bool fullReport,
            const QtReportMetaDataDialog::ReportMetaData& metaData,  QWidget *parent = 0);

};

} // namespace qt

} // namespace iris

#endif // QT_SENSORCONFIGURATIONREPORT_H
