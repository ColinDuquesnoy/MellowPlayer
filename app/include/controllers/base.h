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

#ifndef BASECONTROLLER_H
#define BASECONTROLLER_H

//---------------------------------------------------------
// Headers
//---------------------------------------------------------
#include <QObject>

//---------------------------------------------------------
// Forward declarations
//---------------------------------------------------------
class MainWindow;

//---------------------------------------------------------
// Classes
//---------------------------------------------------------
/**
 * @brief Base class for controllers.
 *
 * Take care of maintaining a pointer to the main window.
 *
 * Subclasses may want to override BaseController::applyPreferences() to
 * apply specific preferences.
 */
class BaseController : public QObject {
  Q_OBJECT
  friend class MainWindow;

public:
  /**
   * @brief Constructor
   * @param name Name of the controller. This name can later be used to retrieve
   * a controller
   * instance from the main window (see MainWindow::controller)
   * @param parent Parent object, MainWindow.
   */
  explicit BaseController(const QString &name, MainWindow *parent = 0);

  /**
   * @brief Called after user made some changes to the preferences.
   *
   * Controllers should implement this method if they rely a on QSettings.
   */
  virtual void applyPreferences();

protected:
  MainWindow *m_mainWindow;
};

#endif // BASECONTROLLER_H
