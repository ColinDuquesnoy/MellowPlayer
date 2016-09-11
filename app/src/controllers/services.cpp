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
#include "controllers/player.h"
#include "controllers/services.h"
#include "utils/icons.h"
#include "views/dlgselectservice.h"
#include "views/mainwindow.h"
#include "views/webview.h"
#include "ui_mainwindow.h"

//---------------------------------------------------------
// Implementations
//---------------------------------------------------------
//--------------------------------------
QString findFileByExtension(const QString &directory, const QString &suffix) {
  foreach (const QFileInfo &fileInfo,
           QDir(directory).entryInfoList(QDir::Files | QDir::NoDotAndDotDot)) {
    if (fileInfo.isFile() && fileInfo.suffix() == suffix)
      return fileInfo.absoluteFilePath();
  }
  return QString();
}

//--------------------------------------
QString findTranslation(const QString &originalFilePath,
                        const QString &locale) {
  QString baseName = QFileInfo(originalFilePath).baseName();
  QString expectedPath =
      QString(originalFilePath)
          .replace(baseName, QString("%1_%2").arg(baseName).arg((locale)));
  if (QFileInfo(expectedPath).exists())
    return expectedPath;
  return QString();
}

//--------------------------------------
QString readFileContent(const QString &filePath) {
  QString retVal;

  QFile file(filePath);
  if (!file.open(QIODevice::ReadOnly)) {
    return retVal;
  }

  QTextStream in(&file);
  retVal = in.readAll();
  file.close();

  return retVal;
}

//--------------------------------------
void readMetadata(const QString &filePath, StreamingServicePlugin &plugin) {
  QSettings meta(filePath, QSettings::IniFormat);

  plugin.Author = meta.value("author").toString();
  plugin.AuthorWebSite = meta.value("author_website").toString();
  plugin.IconFilePath =
      QFileInfo(QFileInfo(filePath).dir(), meta.value("icon").toString())
          .absoluteFilePath();
  plugin.Icon = QIcon(plugin.IconFilePath);
  plugin.Name = meta.value("name").toString();
  plugin.Url = meta.value("url").toString();
  plugin.Version = meta.value("version").toString();
}

//--------------------------------------
StreamingServicePlugin loadPlugin(const QString &directory) {
  QString metadataPath = findFileByExtension(directory, "ini");
  QString scriptPath = findFileByExtension(directory, "js");
  QString descPath = findFileByExtension(directory, "html");
  QString locale = QLocale::system().name().split("_")[0];
  QString translationPath = findTranslation(descPath, locale);
  if (!translationPath.isEmpty())
    descPath = translationPath;
  StreamingServicePlugin retVal;
  retVal.Code = readFileContent(scriptPath);
  retVal.Description = readFileContent(descPath);
  readMetadata(metadataPath, retVal);
  retVal.scriptPath = scriptPath;

  return retVal;
}

//--------------------------------------
bool checkPluginDirectory(const QString &directory) {
  QString metadataPath = findFileByExtension(directory, "ini");
  QString scriptPath = findFileByExtension(directory, "js");
  QString descPath = findFileByExtension(directory, "html");

  return !scriptPath.isEmpty() && !metadataPath.isEmpty() &&
         !descPath.isEmpty();
}

//--------------------------------------
QStringList getSearchPaths() {
  QStringList paths;
  paths.append(QFileInfo(QDir::currentPath(), "plugins").absoluteFilePath());
  paths.append(QFileInfo(qApp->applicationDirPath(), "plugins").absoluteFilePath());
  paths.append(getUserPluginsDirectory());

#ifdef Q_OS_MAC
  QDir pluginsDir(qApp->applicationDirPath());
  pluginsDir.cdUp();
  pluginsDir.cd("PlugIns");
  pluginsDir.cd("services");
  paths.append(pluginsDir.path());
  qWarning() << "OSX Application Plugins Path:" << pluginsDir.path();
#endif

#ifdef Q_OS_LINUX
  paths.append("/usr/share/mellowplayer/plugins");
  paths.append("/usr/local/share/mellowplayer/plugins");
#endif

  return paths;
}

//--------------------------------------
QList<StreamingServicePlugin> loadPlugins() {
  QList<StreamingServicePlugin> plugins;
  auto searchPaths = getSearchPaths();
  qInfo() << "Plugins search path: " << searchPaths;
  foreach (const QString &path, searchPaths) {
    qInfo() << "Looking for plugins in " << path;
    foreach (const QFileInfo &directory,
             QDir(path).entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot)) {
      if (checkPluginDirectory(directory.absoluteFilePath())) {
        StreamingServicePlugin plugin =
            loadPlugin(directory.absoluteFilePath());
        if (plugin.isValid() && !plugins.contains(plugin)) {
          qInfo() << plugin.Name << "plugin successfully loaded (from "
                  << directory.absoluteFilePath() << ")";
          plugins.append(plugin);
        }
      }
    }
  }
  return plugins;
}

//--------------------------------------
QString getUserPluginsDirectory() {
  return QFileInfo(QStandardPaths::standardLocations(
                       QStandardPaths::AppLocalDataLocation)[0],
                   "plugins")
      .absoluteFilePath();
}

//--------------------------------------
bool StreamingServicePlugin::isValid() {
  return !Name.isEmpty() && !Url.isEmpty();
}

//--------------------------------------
StreamingServicesController::StreamingServicesController(MainWindow *mainWindow)
    : BaseController("services", mainWindow) {
  m_services = loadPlugins();

  foreach (StreamingServicePlugin p, m_services) {
    m_fsWatcher.addPath(p.scriptPath);
  }

  QPushButton *bt = m_mainWindow->ui()->pushButtonSelect;
  QAction *a = m_mainWindow->ui()->actionSelect_service;
  WebView *v = m_mainWindow->ui()->webView;

  connect(bt, &QPushButton::clicked, this,
          &StreamingServicesController::selectService);
  connect(a, &QAction::triggered, this,
          &StreamingServicesController::selectService);
  connect(v, &WebView::loadStarted, this,
          &StreamingServicesController::onLoadStarted);
  connect(v, &WebView::loadFinished, this,
          &StreamingServicesController::onLoadFinished);
  connect(m_mainWindow->ui()->actionHome, &QAction::triggered, this,
          &StreamingServicesController::onHomeTriggered);
  connect(&m_fsWatcher, &QFileSystemWatcher::fileChanged, this,
          &StreamingServicesController::onScriptChanged);
}

//--------------------------------------
void StreamingServicesController::reload() {
  foreach (StreamingServicePlugin p, m_services) {
    m_fsWatcher.removePath(p.scriptPath);
  }
  m_services = loadPlugins();
  foreach (StreamingServicePlugin p, m_services) {
    if (m_currentService.Name == p.Name)
      m_currentService = p;
    m_fsWatcher.addPath(p.scriptPath);
  }
}

//--------------------------------------
void StreamingServicesController::startService(const QString &serviceName,
                                               bool force) {
  StreamingServicePlugin sv = getService(serviceName);
  if (sv.isValid()) {
    m_mainWindow->ui()->stackedWidget->setCurrentIndex(PAGE_WEB);
    if (sv.Name != m_currentService.Name || force) {
      m_currentService = sv;
      m_mainWindow->setWindowTitle(m_currentService.Name);

      QSettings().setValue("services/current", sv.Name);
      WebView *v = m_mainWindow->ui()->webView;
      v->load(QUrl(sv.Url));
      qDebug() << "Starting service" << serviceName;

      QAction *a = v->pageAction(QWebEnginePage::Back);
      a->setIcon(Icons::back());
      m_mainWindow->ui()->toolBar->insertAction(m_mainWindow->ui()->actionHome,
                                                a);
      a = v->pageAction(QWebEnginePage::Forward);
      a->setIcon(Icons::forward());
      m_mainWindow->ui()->toolBar->insertAction(m_mainWindow->ui()->actionHome,
                                                a);
      a = v->pageAction(QWebEnginePage::Reload);
      a->setIcon(Icons::reload());
      m_mainWindow->ui()->toolBar->insertAction(m_mainWindow->ui()->actionHome,
                                                a);
    }
  } else {
    m_currentService = sv;
    m_mainWindow->ui()->stackedWidget->setCurrentIndex(PAGE_HOME);
  }
}

//--------------------------------------
const QList<StreamingServicePlugin> &
StreamingServicesController::services() const {
  return m_services;
}

//--------------------------------------
StreamingServicePlugin
StreamingServicesController::getService(const QString &serviceName) const {
  foreach (StreamingServicePlugin plugin, m_services) {
    if (plugin.Name.toLower() == serviceName.toLower())
      return plugin;
    if (plugin.Name.toLower().replace(" ", "") == serviceName.toLower())
        return plugin;
  }
  return StreamingServicePlugin();
}

//--------------------------------------
const StreamingServicePlugin &
StreamingServicesController::currentService() const {
  return m_currentService;
}

//--------------------------------------
void StreamingServicesController::selectService() {
  QString retVal = DlgSelectServices::selectService(m_mainWindow);
  if (!retVal.isEmpty()) {
    startService(retVal);
  }
}

//--------------------------------------
void StreamingServicesController::onHomeTriggered() {
  startService(m_currentService.Name, true);
}

//--------------------------------------
void StreamingServicesController::onLoadStarted() {
  m_mainWindow->setInfoLabelText(
      QString("Loading %1").arg(m_currentService.Name));
  m_mainWindow->player()->stopPolling();
}

//--------------------------------------
void StreamingServicesController::loadCurrentServiceScript() {
  QString constants("mellowplayer = {\n"
                    "    PlaybackStatus: {\n"
                    "        PLAYING: 0,\n"
                    "        PAUSED: 1,\n"
                    "        STOPPED: 2,\n"
                    "        BUFFERING: 3\n"
                    "    }\n"
                    "};");
  this->m_mainWindow->ui()->webView->page()->runJavaScript(
      constants + m_currentService.Code);
}

//--------------------------------------
void StreamingServicesController::onLoadFinished(bool status) {
  WebView *v = m_mainWindow->ui()->webView;
  if (status && !v->url().isEmpty()) {
    loadCurrentServiceScript();
    m_mainWindow->player()->startPolling();
    emit serviceStarted(m_currentService.Name);
    qDebug() << "Service started" << m_currentService.Name;
  }
}

void StreamingServicesController::onScriptChanged(const QString &path) {
  foreach (StreamingServicePlugin p, m_services) {
    if (p.scriptPath == path) {
      qDebug() << "script changed externally, reloading" << path;
      p.Code = readFileContent(path);
      if (p.Name == m_currentService.Name) {
        m_currentService.Code = p.Code;
        loadCurrentServiceScript();
      }
      break;
    }
  }
  m_fsWatcher.addPath(path);
}

//--------------------------------------
bool operator==(const StreamingServicePlugin &lhs,
                const StreamingServicePlugin &rhs) {
  return lhs.Name == rhs.Name;
}
