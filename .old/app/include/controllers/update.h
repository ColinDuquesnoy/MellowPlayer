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

#ifndef UPDATECONTROLLER_H
#define UPDATECONTROLLER_H

//---------------------------------------------------------
// Headers
//---------------------------------------------------------
#include "controllers/base.h"
#include <QString>
#include <QVersionNumber>

//---------------------------------------------------------
// Forward declarations
//---------------------------------------------------------
class MainWindow;
class QNetworkAccessManager;
class QNetworkReply;

/**
 * @brief Check for updates and warn the user if a new
 * version has been released.
 */
class UpdateController : public BaseController {
  Q_OBJECT
public:
  explicit UpdateController(MainWindow *parent = 0);

private slots:
  void onResultsAvailable(QNetworkReply *reply);
  void onOpenBrowserClicked();
  void onShowDetailsClicked();

private:
  QNetworkAccessManager *m_nam;
  QVersionNumber m_LatestVersion;
  QString m_ReleaseNotes;
};

#endif // UPDATECONTROLLER_H
