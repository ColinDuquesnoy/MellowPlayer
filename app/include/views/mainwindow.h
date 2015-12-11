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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//---------------------------------------------------------
// Headers
//---------------------------------------------------------
#include <QtCore>
#include <QtWidgets>
#include <QCloseEvent>

//---------------------------------------------------------
// Forward declarations
//---------------------------------------------------------
class WebView;
class BaseController;
class StreamingServicesController;
class PlayerController;
namespace Ui {
class MainWindow;
}

//---------------------------------------------------------
// Definitions
//---------------------------------------------------------
#define PAGE_HOME 0
#define PAGE_WEB 1

//---------------------------------------------------------
// Classes
//---------------------------------------------------------
//! Implements the main window of the application.
class MainWindow : public QMainWindow {
  Q_OBJECT
  friend class DlgPreferences;

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  /*!
   * \brief Save window geometry and state
   */
  void saveGeometryAndState();

  /*!
   * \brief setInfoLabelText sets the text shown in the central label of the
   * toolbar.
   *
   * This label is used to display the song's pretty name or the state of the
   * player in case
   * no song are available.
   *
   * \param text
   */
  void setInfoLabelText(const QString &text);

  /**
   * @brief Gets the user interface of the main window.
   */
  Ui::MainWindow *ui() const;

  /**
   * @brief Registers a controller.
   * @param name Name of the controller.
   * @param controller Controller instance.
   */
  void registerController(const QString &name, BaseController *controller);

  /**
   * @brief Gets a controller by name
   * @param name Name of the controller ("services", "player", "hotkeys",
   *    "notifications", "mpris2").
   * @return BaseController instance or nullptr if not found.
   */
  BaseController *controller(const QString &name) const;

  /**
   * @brief Gets the web player controller
   */
  PlayerController *player() const;

  /**
   * @brief Gets the streaming services controller.
   */
  StreamingServicesController *services() const;

  QSystemTrayIcon *trayIcon() const;

public slots:
  /**
   * @brief Resotes window (raise + show).
   */
  void restoreWindow();

private slots:
  void onPageChanged(int pageIndex);
  void onPreferencesTriggered();
  void onAboutTriggered();
  void onAboutQtTriggered();
  void onWikiTriggered();
  void onReportBugTriggered();
  bool exitApplication();
  void onShowMenuToggled(bool showMenu);
  void onShowToolbarToggled(bool showToolBar);
  void onShowFullscreenToggled(bool showFullscreen);
  void onTrayIconActivated(QSystemTrayIcon::ActivationReason reason);

private:
  void closeEvent(QCloseEvent *event);
  void setupIcons();
  void setupActions();
  void setupTrayIcon();
  void connectSlots();
  void restoreGeometryAndState();
  void setupDockMenu();
  void setupToolbar();

  Ui::MainWindow *m_ui;
  QLabel *m_lblSongInfo;
  QToolButton *m_BtMenu;
  QSystemTrayIcon *m_trayIcon;
  QMap<QString, BaseController *> m_controllers;
};

#endif // MAINWINDOW_H
