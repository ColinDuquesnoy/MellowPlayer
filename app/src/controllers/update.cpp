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
#include "controllers/update.h"
#include "ui_mainwindow.h"
#include "views/mainwindow.h"
#include <QDesktopServices>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#define DELAY_BEFORE_CHECK 5000

//---------------------------------------------------------
// Implementations
//---------------------------------------------------------
//-------------------------------------
UpdateController::UpdateController(MainWindow *parent)
    : BaseController("hotkeys", parent),
      m_nam(new QNetworkAccessManager(this)) {
  parent->ui()->popupUpdate->hide();

  m_mainWindow->ui()->pushButtonPopupClose->setIcon(
      QIcon::fromTheme("window-close", QIcon(":/icons/window-close.png")));
  m_mainWindow->ui()->pushButtonPopupOpenBrowser->setIcon(QIcon::fromTheme(
      "internet-web-browser", QIcon(":/icons/internet-web-browser.png")));
  m_mainWindow->ui()->pushButtonPopupDetails->setIcon(QIcon::fromTheme(
      "text-x-changelog", QIcon(":/icons/text-x-changelog.png")));

  connect(m_nam, &QNetworkAccessManager::finished, this,
          &UpdateController::onResultsAvailable);
  connect(m_mainWindow->ui()->pushButtonPopupOpenBrowser, &QPushButton::clicked,
          this, &UpdateController::onOpenBrowserClicked);
  connect(m_mainWindow->ui()->pushButtonPopupDetails, &QPushButton::clicked,
          this, &UpdateController::onShowDetailsClicked);
  m_nam->get(QNetworkRequest(QUrl("https://api.github.com/repos/ColinDuquesnoy/"
                                  "MellowPlayer/releases/latest")));
}

//-------------------------------------
void UpdateController::onResultsAvailable(QNetworkReply *reply) {
  if (reply->error() == QNetworkReply::NoError) {
    QString data(reply->readAll());
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
    QJsonObject obj = doc.object();
    m_LatestVersion = QVersionNumber::fromString(obj.value("name").toString());
    m_ReleaseNotes = obj.value("body").toString().replace("\r\n", "<br>");

    QVersionNumber currentVersion = QVersionNumber::fromString(APP_VERSION);

    if (currentVersion < m_LatestVersion) {
      qDebug() << QString("A new version is available: %1")
                      .arg(m_LatestVersion.toString());
      qDebug() << QString("Release notes:\n\n %1").arg(m_ReleaseNotes);
      m_mainWindow->ui()->popupUpdate->show();
    } else {
      qDebug() << QString("Version %1 is up to date...")
                      .arg(currentVersion.toString());
    }

  } else {
    qDebug() << "Failed to retrieve latest release info from github"
             << reply->errorString();
  }
  reply->deleteLater();
}

//-------------------------------------
void UpdateController::onOpenBrowserClicked() {
  QDesktopServices::openUrl(
      QUrl("https://github.com/ColinDuquesnoy/MellowPlayer/releases/latest"));
}

//-------------------------------------
void UpdateController::onShowDetailsClicked() {
  QMessageBox::information(
      m_mainWindow, "Release notes",
      QString("<b>Latest version: %1</b><p>%2</p>")
          .arg(m_LatestVersion.toString(), m_ReleaseNotes));
}
