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

#ifndef SERVICES_H
#define SERVICES_H

//---------------------------------------------------------
// Headers
//---------------------------------------------------------
#include <QtCore>
#include <QtGui>
#include "controllers/base.h"

//---------------------------------------------------------
// Foward declarations
//---------------------------------------------------------
class MainWindow;

//---------------------------------------------------------
// Structures
//---------------------------------------------------------
/**
 * @brief The StreamingServicePlugin struct contains the plugin data.
 */
struct StreamingServicePlugin {
  QString Code;          ///< Javascript code
  QString Url;           ///< URL of the web service
  QString Name;          ///< Plugin's name
  QString Description;   ///< Plugin's description
  QString Author;        ///< Plugin's author
  QString AuthorWebSite; ///< Website of the plugin's author
  QIcon Icon;            ///< Plugin's icon path
  QString IconFilePath;  ///< Plugin's icon path
  QString Version;       ///< Plugin's version
  bool isValid();
};

bool operator==(const StreamingServicePlugin &lhs,
                const StreamingServicePlugin &rhs);

//---------------------------------------------------------
// Classes
//---------------------------------------------------------
/**
 * @brief Manages the list of plugins and let the user switch between different
 * services.
 */
class StreamingServicesController : public BaseController {
  Q_OBJECT

public:
  explicit StreamingServicesController(MainWindow *mainWindow);

  /**
   * @brief Starts the specified service and show the webview page.
   *
   * If the service does not exists, the home page is shown instead.
   *
   * @param serviceName Name of the service to start (e.g. "Mixcloud", "Deezer",
   * ...)
   */
  void startService(const QString &serviceName, bool force = false);

  /**
   * @brief Gets the list of available streaming services.
   *
   * @return List of service plugin
   */
  const QList<StreamingServicePlugin> &services() const;

  /**
   * @brief Gets the specified service. If the service does not exist, an
   * invalid StreamingServicePlugin will be returned (you can check if valid
   * by calling StreamingServicePlugin.isValid().
   *
   * @param serviceName Name of the service to get (e.g. "Mixcloud", "Deezer",
   * ...)
   *
   * @return A StreamingServicePlugin instance.
   */
  StreamingServicePlugin getService(const QString &serviceName) const;

  /**
   * @brief Gets the current streaming service plugin
   */
  const StreamingServicePlugin &currentService() const;

public slots:
  /**
   * @brief Shows the select service dialog and process change.
   */
  void selectService();
  void onHomeTriggered();

private slots:
  void onLoadStarted();
  void onLoadFinished(bool status);

private:
  QList<StreamingServicePlugin> m_services;
  StreamingServicePlugin m_currentService;
};

#endif // SERVICES_H
