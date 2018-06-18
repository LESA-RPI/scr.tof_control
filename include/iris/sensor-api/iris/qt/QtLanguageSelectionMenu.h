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

#ifndef IRIS_QT_QTLANGUAGESELECTIONMENU_H
#define IRIS_QT_QTLANGUAGESELECTIONMENU_H

#include <QMenu>

class QTranslator;

namespace iris {

namespace qt {

class QtLanguageSelectionMenu: public QMenu {

    Q_OBJECT

    void prepareMenu(const QString& translationFilePrefix, const QString& translationPath);

    QTranslator* translator;

public:

    explicit QtLanguageSelectionMenu(const QString& translationFilePrefix, const QString& translationPath, QWidget *parent = 0);
    explicit QtLanguageSelectionMenu(const QString& translationPath = "translations", QWidget *parent = 0);
    explicit QtLanguageSelectionMenu(QWidget *parent = 0);
    virtual ~QtLanguageSelectionMenu();
    
signals:

    void languageSelected(QString id);
    
private slots:

    void slotLanguageChanged(QAction* item);
    
};

} // namespace qt
} // namespace iris

#endif // IRIS_QT_QTLANGUAGESELECTIONMENU_H
