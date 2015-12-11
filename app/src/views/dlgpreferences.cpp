//-----------------------------------------------------------------------------
//
// This file is part of MellowPlayer.
//
// MellowPlayer is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MellowPlayer is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MellowPlayer.  If not, see <http://www.gnu.org/licenses/>.
//
//-----------------------------------------------------------------------------

//---------------------------------------------------------
// Headers
//---------------------------------------------------------
#include <QFileDialog>
#include <QMessageBox>
#include <QWebEngineCookieStore>
#include "application.h"
#include "utils/icons.h"
#include "utils/shortcuts.h"
#include "views/dlgpreferences.h"
#include "views/mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_dlg_preferences.h"

#define PREFS_INTERFACE 0
#define PREFS_HOTKEYS 1
#define PREFS_NOTIFICATIONS 2
#define PREFS_CACHE 3

//---------------------------------------------------------
// Implementations
//---------------------------------------------------------
//--------------------------------------
DlgPreferences::DlgPreferences(MainWindow *parent)
    : QDialog(parent), m_mainWindow(parent) {
  m_ui = new Ui::DialogPreferences();
  m_ui->setupUi(this);
  setWindowTitle(tr("Preferences"));

  m_ui->listWidget->item(PREFS_INTERFACE)
      ->setIcon(Icons::interfacePreferences());
  m_ui->listWidget->item(PREFS_HOTKEYS)->setIcon(Icons::shortcuts());
  m_ui->listWidget->item(PREFS_NOTIFICATIONS)->setIcon(Icons::notifications());
  m_ui->listWidget->item(PREFS_CACHE)->setIcon(Icons::userTrash());

  connect(m_ui->listWidget, SIGNAL(currentRowChanged(int)), this,
          SLOT(onCategoryChanged(int)));
  connect(m_ui->buttonBox->button(QDialogButtonBox::Reset), SIGNAL(clicked()),
          this, SLOT(reset()));
  connect(m_ui->buttonBox->button(QDialogButtonBox::RestoreDefaults),
          SIGNAL(clicked()), this, SLOT(restoreDefaults()));
  connect(m_ui->lineEditTrayIcon, &QLineEdit::textChanged, this,
          &DlgPreferences::updateTrayIconPreview);

  connect(m_ui->pushButtonClearPreferences, SIGNAL(clicked()), this,
          SLOT(onClearPreferencesClicked()));
  connect(m_ui->pushButtonClearCookies, SIGNAL(clicked()), this,
          SLOT(onClearCookiesClicked()));
  connect(m_ui->pushButtonClearCache, SIGNAL(clicked()), this,
          SLOT(onClearCacheClicked()));

  reset();

  m_ui->listWidget->setCurrentRow(
      QSettings().value("cache/lastSettingsIndex", 0).toInt());
}

//--------------------------------------
DlgPreferences::~DlgPreferences() { delete m_ui; }

//--------------------------------------
bool DlgPreferences::editPreferences(MainWindow *parent) {
  DlgPreferences dlg(parent);
  if (dlg.exec()) {
    QSettings().setValue("cache/lastSettingsIndex",
                         dlg.m_ui->stackedWidget->currentIndex());
    dlg.applyInterface();
    dlg.applyShortcuts();
    dlg.applyNotifications();
    return true;
  }
  return false;
}

//--------------------------------------
void DlgPreferences::onCategoryChanged(int category) {
  m_ui->stackedWidget->setCurrentIndex(category);
}

//--------------------------------------
void DlgPreferences::reset() {
  resetInterface();
  resetShortcuts();
  resetNotifications();
}

//--------------------------------------
void DlgPreferences::restoreDefaults() {
  restoreInterface();
  restoreShortcuts();
  restoreNotifications();
}

//--------------------------------------
void DlgPreferences::restart() {
  if (QMessageBox::question(
          this, tr("Restart required"),
          tr("You need to restart the application for the change to be applied."
             "\n\n"
             "Do you want to restart now?"),
          QMessageBox::Yes | QMessageBox::No,
          QMessageBox::Yes) == QMessageBox::Yes) {
    QProcess::startDetached(QApplication::applicationFilePath());
    MellowPlayerApp *app = qobject_cast<MellowPlayerApp *>(qApp);
    app->close();
    qApp->exit(12);
  }
}

//--------------------------------------
void DlgPreferences::onClearPreferencesClicked() {
  if (QMessageBox::question(
          this, tr("Clear settings"),
          tr("This will remove all settings stored by MellowPlayer and restart "
             "the application...\n"
             "Are you sure you want to erase all settings?"),
          QMessageBox::Yes | QMessageBox::No,
          QMessageBox::No) == QMessageBox::Yes) {
    QSettings().clear();
    restart();
  }
}

//--------------------------------------
void DlgPreferences::onClearCookiesClicked() {
  if (QMessageBox::question(
          this, tr("Clear cookies"),
          tr("This will remove all cookies stored by MellowPlayer.\n"
             "Are you sure you want to proceed?"),
          QMessageBox::Yes | QMessageBox::No,
          QMessageBox::No) == QMessageBox::Yes) {
    m_mainWindow->ui()->webView->deleteAllCookies();
  }
}

//--------------------------------------
void DlgPreferences::onClearCacheClicked() {
  if (QMessageBox::question(
          this, tr("Clear cookies"),
          tr("This will remove all cookies stored by MellowPlayer.\n"
             "Are you sure you want to proceed?"),
          QMessageBox::Yes | QMessageBox::No,
          QMessageBox::No) == QMessageBox::Yes) {
    QString cacheDir =
        QStandardPaths::standardLocations(QStandardPaths::CacheLocation)[0];
    QDir(cacheDir).removeRecursively();
  }
}

//--------------------------------------
void DlgPreferences::resetInterface() {
  bool minimizeToTray =
      QSettings().value("interface/minimizeToTray", QVariant(true)).toBool();
  bool showTrayIcon =
      QSettings().value("interface/showTrayIcon", QVariant(true)).toBool();
  QString trayIconPath = QSettings().value("interface/trayIcon").toString();
  bool confirmQuit = QSettings().value("interface/confirmQuit", true).toBool();

  m_ui->checkBoxConfirmQuit->setChecked(confirmQuit);
  m_ui->checkBoxShowTrayIcon->setChecked(showTrayIcon);
  m_ui->groupBoxMinimizeToTray->setChecked(minimizeToTray);
  m_ui->lineEditTrayIcon->setText(trayIconPath);
  updateTrayIconPreview(trayIconPath);
}

//--------------------------------------
void DlgPreferences::resetShortcuts() {
  QList<QAction *> actions;
  actions.append(m_mainWindow->m_ui->actionPlayPause);
  actions.append(m_mainWindow->m_ui->actionNext);
  actions.append(m_mainWindow->m_ui->actionPrevious);
  actions.append(m_mainWindow->m_ui->actionAdd_to_favorites);

  QList<QString> shortcuts;
  shortcuts.append(DEFAULT_SHORTCUT_PLAY);
  shortcuts.append(DEFAULT_SHORTCUT_NEXT);
  shortcuts.append(DEFAULT_SHORTCUT_PREVIOUS);
  shortcuts.append(DEFAULT_SHORTCUT_FAVORITE);

  QList<QKeySequenceEdit *> edits;
  edits.append(m_ui->lineEditPlayPause);
  edits.append(m_ui->lineEditNext);
  edits.append(m_ui->lineEditPrevious);
  edits.append(m_ui->lineEditFavorite);

  for (int i = 0; i < actions.count(); ++i)
    edits[i]->setKeySequence(
        QSettings()
            .value(QString("hotkeys/") + actions[i]->objectName(), shortcuts[i])
            .toString());
}

//--------------------------------------
void DlgPreferences::resetNotifications() {
  m_ui->groupBoxEnableNotifs->setChecked(
      QSettings().value("notifications/enable", true).toBool());
  m_ui->checkBoxNotifSongChanged->setChecked(
      QSettings().value("notifications/enableSongChanged", true).toBool());
  m_ui->checkBoxNotifPaused->setChecked(
      QSettings().value("notifications/enablePaused", false).toBool());
  m_ui->checkBoxNotifStopped->setChecked(
      QSettings().value("notifications/enableStopped", false).toBool());
  m_ui->checkBoxNotifActions->setChecked(
      QSettings().value("notifications/enableActions", true).toBool());
  m_ui->spinBoxNotifTimeout->setValue(
      QSettings().value("notifications/timeout", 5).toInt());
}

//--------------------------------------
void DlgPreferences::restoreInterface() {
  QSettings().setValue("interface/minimizeToTray", true);
  QSettings().setValue("interface/showTrayIcon", true);
  QSettings().setValue("interface/trayIcon", "");
  QSettings().setValue("interface/confirmQuit", true);

  resetInterface();
}

//--------------------------------------
void DlgPreferences::restoreShortcuts() {
  QList<QAction *> actions;
  actions.append(m_mainWindow->m_ui->actionPlayPause);
  actions.append(m_mainWindow->m_ui->actionNext);
  actions.append(m_mainWindow->m_ui->actionPrevious);
  actions.append(m_mainWindow->m_ui->actionAdd_to_favorites);

  QList<QString> shortcuts;
  shortcuts.append(DEFAULT_SHORTCUT_PLAY);
  shortcuts.append(DEFAULT_SHORTCUT_NEXT);
  shortcuts.append(DEFAULT_SHORTCUT_PREVIOUS);
  shortcuts.append(DEFAULT_SHORTCUT_FAVORITE);

  for (int i = 0; i < actions.count(); ++i)
    QSettings().setValue(QString("hotkeys/") + actions[i]->objectName(),
                         shortcuts[i]);

  resetShortcuts();
}

//--------------------------------------
void DlgPreferences::restoreNotifications() {
  QSettings().setValue("notifications/enable", true);
  QSettings().setValue("notifications/enableSongChanged", true);
  QSettings().setValue("notifications/enablePaused", false);
  QSettings().setValue("notifications/enableStopped", false);
  QSettings().setValue("notifications/enableActions", true);
  QSettings().setValue("notifications/timeout", 5);
}

//--------------------------------------
void DlgPreferences::applyInterface() {
  QSettings().setValue("interface/minimizeToTray",
                       m_ui->groupBoxMinimizeToTray->isChecked());
  QSettings().setValue("interface/showTrayIcon",
                       m_ui->checkBoxShowTrayIcon->isChecked());
  QSettings().setValue("interface/confirmQuit",
                       m_ui->checkBoxConfirmQuit->isChecked());
  QSettings().setValue("interface/trayIcon", m_ui->lineEditTrayIcon->text());
}

//--------------------------------------
void DlgPreferences::applyShortcuts() {
  QList<QAction *> actions;
  actions.append(m_mainWindow->m_ui->actionPlayPause);
  actions.append(m_mainWindow->m_ui->actionNext);
  actions.append(m_mainWindow->m_ui->actionPrevious);
  actions.append(m_mainWindow->m_ui->actionAdd_to_favorites);

  QList<QKeySequenceEdit *> edits;
  edits.append(m_ui->lineEditPlayPause);
  edits.append(m_ui->lineEditNext);
  edits.append(m_ui->lineEditPrevious);
  edits.append(m_ui->lineEditFavorite);

  for (int i = 0; i < actions.count(); ++i) {
    QSettings().setValue(QString("hotkeys/") + actions[i]->objectName(),
                         edits[i]->keySequence().toString());
    actions[i]->setShortcut(edits[i]->keySequence());
  }
}

//--------------------------------------
void DlgPreferences::applyNotifications() {
  QSettings().setValue("notifications/enable",
                       m_ui->groupBoxEnableNotifs->isChecked());
  QSettings().setValue("notifications/enableSongChanged",
                       m_ui->checkBoxNotifSongChanged->isChecked());
  QSettings().setValue("notifications/enablePaused",
                       m_ui->checkBoxNotifPaused->isChecked());
  QSettings().setValue("notifications/enableStopped",
                       m_ui->checkBoxNotifStopped->isChecked());
  QSettings().setValue("notifications/enableActions",
                       m_ui->checkBoxNotifActions->isChecked());
  QSettings().setValue("notifications/timeout",
                       m_ui->spinBoxNotifTimeout->value());
}

//--------------------------------------
void DlgPreferences::updateTrayIconPreview(const QString &value) {
  QIcon icon;
  if (value.trimmed().isEmpty())
    icon = qApp->windowIcon();
  else if (value.startsWith(":/icons") || QFile::exists(value))
    icon = QIcon(value);
  else
    icon = QIcon::fromTheme(value);
  m_ui->lblTrayIcon->setPixmap(icon.pixmap(24, 24));
}
