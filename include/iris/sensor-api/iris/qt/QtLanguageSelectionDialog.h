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



#ifndef IRIS_QT_QTLANGUAGESELECTIONDIALOG_H
#define IRIS_QT_QTLANGUAGESELECTIONDIALOG_H

#include <QDialog>

class QTranslator;

namespace Ui {
    class QtLanguageSelectionDialog;
}

namespace iris {

namespace qt {

class QtLanguageSelectionDialog : public QDialog
{
    Q_OBJECT

protected:

    QTranslator* translator;
    QString selectedLanguage;

protected slots:

    void languageSelected(void);

public:
    explicit QtLanguageSelectionDialog(const QString& translationFilePrefix, const QString& translationPath, QWidget *parent = 0);
    explicit QtLanguageSelectionDialog(const QString& translationPath = "translations", QWidget *parent = 0);
    explicit QtLanguageSelectionDialog(QWidget *parent = 0);
    virtual ~QtLanguageSelectionDialog();

    QString getSelectedLanguage(void);

private:
    Ui::QtLanguageSelectionDialog *ui;
    void prepareForm(const QString& translationFilePrefix, const QString& translationPath);
};

} // namespace qt

} // namespace iris

#endif // IRIS_QT_QTLANGUAGESELECTIONDIALOG_H
