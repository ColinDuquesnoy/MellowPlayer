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

#ifndef DLGPREFERENCES_H
#define DLGPREFERENCES_H

//---------------------------------------------------------
// Headers
//---------------------------------------------------------
#include <QMainWindow>
#include <QDialog>
#include <QIcon>

//---------------------------------------------------------
// Forward declarations
//---------------------------------------------------------
namespace Ui {
class DialogPreferences;
}
class MainWindow;

//---------------------------------------------------------
// Class declarations
//---------------------------------------------------------
/*!
 * \brief The DlgPreferences class implement the preferences dialog.
 */
class DlgPreferences : public QDialog {
  Q_OBJECT
public:
  explicit DlgPreferences(MainWindow *parent = NULL);
  ~DlgPreferences();
  /*!
   * \brief Convenience method for editing the application
   * preferences
   *
   * \param parent Parent widget of the dialog.
   * \return True if the dialog was accepted.
   */
  static bool editPreferences(MainWindow *parent);

private slots:
  void onCategoryChanged(int category);
  void reset();
  void restoreDefaults();
  void onClearPreferencesClicked();
  void onClearCookiesClicked();
  void onClearCacheClicked();

private:
  void restart();

  void resetInterface();
  void resetShortcuts();
  void resetNotifications();

  void restoreInterface();
  void restoreShortcuts();
  void restoreNotifications();

  void applyInterface();
  void applyShortcuts();
  void applyNotifications();

  void updateTrayIconPreview(const QString &value);

private:
  Ui::DialogPreferences *m_ui;
  MainWindow *m_mainWindow;
};

#endif // DLGPREFERENCES_H
