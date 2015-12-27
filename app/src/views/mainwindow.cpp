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
#include <QDesktopServices>
#include <QMessageBox>
#include <QWebEnginePage>
#include <QWebEngineSettings>
#include "controllers/hotkeys.h"
#include "controllers/mpris2.h"
#include "controllers/notifications.h"
#include "controllers/player.h"
#include "controllers/services.h"
#include "utils/icons.h"
#include "utils/shortcuts.h"
#include "views/dlgselectservice.h"
#include "views/dlgpreferences.h"
#include "views/mainwindow.h"
#include "ui_mainwindow.h"

//---------------------------------------------------------
// Implementations
//---------------------------------------------------------
//-------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_ui(new Ui::MainWindow), m_lblSongInfo(NULL) {
  m_ui->setupUi(this);
  setupActions();
  setupIcons();
  setupTrayIcon();
  setupDockMenu();
  setupToolbar();
  connectSlots();
  restoreGeometryAndState();
  m_ui->stackedWidget->setCurrentIndex(PAGE_HOME);
  onPageChanged(PAGE_HOME);

  // Setup controllers
  new PlayerController(this);
  new StreamingServicesController(this);
  new NotificationsController(this);
  new HotkeysController(this);
  new MPRIS2Controller(this);
}

//-------------------------------------
MainWindow::~MainWindow() {
    foreach(BaseController* c, m_controllers){
        c->m_mainWindow = nullptr;
    }
    delete m_ui;
}

//--------------------------------------
void MainWindow::onPreferencesTriggered() {
  restoreWindow();
  DlgPreferences::editPreferences(this);
  bool minimizeToTray =
      QSettings().value("interface/minimizeToTray", QVariant(true)).toBool();
  bool showTrayIcon =
      QSettings().value("interface/showTrayIcon", QVariant(true)).toBool();
  m_trayIcon->setVisible(minimizeToTray && showTrayIcon);
  m_trayIcon->setIcon(Icons::trayIcon());

  foreach (BaseController *controller, m_controllers.values()) {
    controller->applyPreferences();
  }
}

//--------------------------------------
void MainWindow::closeEvent(QCloseEvent *event) {
  bool minimizeToTray =
      QSettings().value("interface/minimizeToTray", QVariant(true)).toBool();
  if (isVisible() && minimizeToTray &&
      m_ui->stackedWidget->currentIndex() == PAGE_WEB) {
    bool showMsg =
        QSettings().value("interface/showMinimizeToTrayMsg", true).toBool();
    if (showMsg) {
      QMessageBox::information(
          this, tr("Minimizing to system tray"),
          tr("The program will keep running in the system tray. To terminate "
             "the program, choose <b>Quit</b> in the context menu of the "
             "system tray entry."));
      QSettings().setValue("interface/showMinimizeToTrayMsg", false);
    }
    hide();
    event->ignore();
  } else {
    player()->stopPolling();
    hide();
    qApp->processEvents();
    qApp->quit();
  }
}

//--------------------------------------
void MainWindow::setupIcons() {
  m_ui->pushButtonSelect->setIcon(Icons::selectStreamingService());
  m_ui->pushButtonPreferences->setIcon(Icons::preferences());
  m_ui->pushButtonQuit->setIcon(Icons::quit());
}

//--------------------------------------
void MainWindow::setupActions() {
  // load custom user shortcuts for player actions
  QString defaults[] = {DEFAULT_SHORTCUT_PLAY, DEFAULT_SHORTCUT_NEXT,
                        DEFAULT_SHORTCUT_PREVIOUS, DEFAULT_SHORTCUT_FAVORITE};
  QAction *actions[] = {m_ui->actionPlayPause, m_ui->actionNext,
                        m_ui->actionPrevious, m_ui->actionAdd_to_favorites};
  for (int i = 0; i < 4; ++i) {
    QAction *a = actions[i];
    addAction(a);
    a->setShortcut(
        QSettings()
            .value(QString("hotkeys/") + a->objectName(), defaults[i])
            .toString());
  }
  // most services don't support that, hide to avoid seeing it during
  // the loading of the service
  m_ui->actionAdd_to_favorites->setVisible(false);

  // setup roles, this is only for OS X
  m_ui->actionPreferences->setMenuRole(QAction::PreferencesRole);
  m_ui->actionSelect_service->setMenuRole(QAction::ApplicationSpecificRole);
  m_ui->actionQuit->setMenuRole(QAction::QuitRole);
  m_ui->actionAbout_MellowPlayer->setMenuRole(QAction::AboutRole);
  m_ui->actionAbout_Qt->setMenuRole(QAction::AboutQtRole);

  // add web page navigation actions
  QAction *a = m_ui->webView->pageAction(QWebEnginePage::Back);
  a->setIcon(Icons::back());
  m_ui->menuNavigation->addAction(a);
  a = m_ui->webView->pageAction(QWebEnginePage::Forward);
  a->setIcon(Icons::forward());
  m_ui->menuNavigation->addAction(a);
  a = m_ui->webView->pageAction(QWebEnginePage::Reload);
  a->setIcon(Icons::reload());
  m_ui->menuNavigation->addAction(a);

  // set user defined view actions state
  m_ui->actionShow_menu->setChecked(
      QSettings().value("interface/menuVisible", false).toBool());
  m_ui->actionShow_toolbar->setChecked(
      QSettings().value("interface/toolBarVisible", true).toBool());
  m_ui->actionFullscreen->setChecked(
      QSettings().value("interface/showFullscreen", false).toBool());

#ifndef Q_OS_MACX
  addAction(m_ui->actionShow_menu);
  addAction(m_ui->actionShow_toolbar);
  addAction(m_ui->actionFullscreen);
#else
  // Menu cannot be hidden on OSX
  m_ui->actionShow_menu->setVisible(false);
  m_ui->actionShow_toolbar->setVisible(false);
  m_ui->actionFullscreen->setVisible(false);
#endif
  addAction(m_ui->actionSelect_service);
  addAction(m_ui->actionPreferences);
  addAction(m_ui->actionPlayPause);
  addAction(m_ui->actionPrevious);
  addAction(m_ui->actionNext);
  addAction(m_ui->actionAdd_to_favorites);
  addAction(m_ui->actionQuit);
}

//--------------------------------------
void MainWindow::setupTrayIcon() {
  m_trayIcon = new QSystemTrayIcon(this);

  QMenu *mnu = new QMenu();
  mnu->addAction(m_ui->actionPlayPause);
  mnu->addAction(m_ui->actionNext);
  mnu->addAction(m_ui->actionPrevious);
  mnu->addSeparator();
  mnu->addAction(m_ui->actionSelect_service);
  mnu->addAction(m_ui->actionPreferences);
  mnu->addSeparator();
  //  QAction *actionRestore =
  //      mnu->addAction(QIcon::fromTheme("view-restore"), "Restore");
  mnu->addAction(m_ui->actionRestoreWindow);
  mnu->addSeparator();
  mnu->addAction(m_ui->actionQuit);

  m_trayIcon->setContextMenu(mnu);

  bool minimizeToTray =
      QSettings().value("interface/minimizeToTray", QVariant(true)).toBool();
  bool showTrayIcon =
      QSettings().value("interface/showTrayIcon", QVariant(true)).toBool();
  m_trayIcon->setIcon(Icons::trayIcon());
  m_trayIcon->setVisible(minimizeToTray && showTrayIcon);

  //  connect(actionRestore, &QAction::triggered, this, &MainWindow::show);
  connect(m_trayIcon, &QSystemTrayIcon::activated, this,
          &MainWindow::onTrayIconActivated);
}

//--------------------------------------
void MainWindow::connectSlots() {
  connect(m_ui->actionRestoreWindow, SIGNAL(triggered()), this,
          SLOT(restoreWindow()));
  connect(m_ui->actionPreferences, SIGNAL(triggered()), this,
          SLOT(onPreferencesTriggered()));
  connect(m_ui->pushButtonPreferences, SIGNAL(clicked()), this,
          SLOT(onPreferencesTriggered()));

  connect(m_ui->actionQuit, SIGNAL(triggered()), this, SLOT(exitApplication()));
  connect(m_ui->pushButtonQuit, SIGNAL(clicked()), this,
          SLOT(exitApplication()));

  connect(m_ui->actionAbout_MellowPlayer, SIGNAL(triggered()), this,
          SLOT(onAboutTriggered()));
  connect(m_ui->actionAbout_Qt, SIGNAL(triggered()), this,
          SLOT(onAboutQtTriggered()));
  connect(m_ui->actionReport_a_bug, SIGNAL(triggered()), this,
          SLOT(onReportBugTriggered()));
  connect(m_ui->actionWiki, SIGNAL(triggered()), this, SLOT(onWikiTriggered()));
  connect(m_ui->actionShow_menu, SIGNAL(toggled(bool)), this,
          SLOT(onShowMenuToggled(bool)));
  connect(m_ui->actionShow_toolbar, SIGNAL(toggled(bool)), this,
          SLOT(onShowToolbarToggled(bool)));
  connect(m_ui->actionFullscreen, SIGNAL(toggled(bool)), this,
          SLOT(onShowFullscreenToggled(bool)));

  connect(m_ui->stackedWidget, &QStackedWidget::currentChanged, this,
          &MainWindow::onPageChanged);
}

//--------------------------------------
static QString compilerString() {
#if defined(                                                                   \
    Q_CC_CLANG) // must be before GNU, because clang claims to be GNU too
  QString isAppleString;
#if defined(__apple_build_version__) // Apple clang has other version numbers
  isAppleString = QLatin1String(" (Apple)");
#endif
  return QLatin1String("Clang ") + QString::number(__clang_major__) +
         QLatin1Char('.') + QString::number(__clang_minor__) + isAppleString;
#elif defined(Q_CC_GNU)
  return QLatin1String("GCC ") + QLatin1String(__VERSION__);
#elif defined(Q_CC_MSVC)
  if (_MSC_VER >= 1800) // 1800: MSVC 2013 (yearly release cycle)
    return QLatin1String("MSVC ") +
           QString::number(2008 + ((_MSC_VER / 100) - 13));
  if (_MSC_VER >=
      1500) // 1500: MSVC 2008, 1600: MSVC 2010, ... (2-year release cycle)
    return QLatin1String("MSVC ") +
           QString::number(2008 + 2 * ((_MSC_VER / 100) - 15));
#endif
  return QLatin1String("<unknown compiler>");
}

//--------------------------------------
void MainWindow::onAboutTriggered() {
  restoreWindow();
  QString version = QString("%1.%2.%3%4")
                        .arg(VERSION_MAJOR)
                        .arg(VERSION_MINOR)
                        .arg(VERSION_MICRO)
                        .arg(VERSION_STATUS);

  const QString description =
      tr("<h3>MellowPlayer %1</h3>"
         "Built on %2 at %3 (%4, %5 bit)<br/>"
         "<br/>"
         "Copyright 2015 Colin Duquesnoy. All rights reserved.<br/>"
         "<br/>"
         "The program is provided AS IS with NO WARRANTY OF ANY KIND, "
         "INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A "
         "PARTICULAR PURPOSE.<br/><br/>"
#ifndef Q_OS_LINUX
         "<a href=\"http://colinduquesnoy.github.io/MellowPlayer/\">Click here "
         "to download the latest version!</a> "
#endif
         )
          .arg(version, QLatin1String(__DATE__), QLatin1String(__TIME__),
               compilerString(), QString::number(QSysInfo::WordSize));

  QMessageBox::about(this, tr("About MellowPlayer"), description);
}

//--------------------------------------
void MainWindow::onAboutQtTriggered() { QMessageBox::aboutQt(this); }

//--------------------------------------
void MainWindow::onWikiTriggered() {
  QDesktopServices::openUrl(
      QUrl("https://github.com/ColinDuquesnoy/MellowPlayer/"
           "wiki#user-documentation"));
}

//--------------------------------------
void MainWindow::onReportBugTriggered() {
  QDesktopServices::openUrl(
      QUrl("https://github.com/ColinDuquesnoy/MellowPlayer/issues/new"));
}

//--------------------------------------
bool MainWindow::exitApplication() {
  bool confirm = QSettings().value("interface/confirmQuit", true).toBool();
  if (confirm) {
    int answer = QMessageBox::question(
        this, tr("Confirm quit"), tr("Are you sure you want to exit %1?")
                                      .arg(qApp->applicationDisplayName()),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (answer == QMessageBox::No)
      return false;
  }
  qApp->exit();
  return true;
}

//--------------------------------------
void MainWindow::restoreWindow() {
  raise();
  show();
}

//--------------------------------------
void MainWindow::onShowMenuToggled(bool showMenu) {
  QSettings().setValue("interface/menuVisible", showMenu);
  m_ui->menuBar->setVisible(showMenu);
}

//--------------------------------------
void MainWindow::onShowToolbarToggled(bool showToolBar) {
  QSettings().setValue("interface/toolBarVisible", showToolBar);

#ifndef Q_OS_MACX
  m_ui->toolBar->setVisible(showToolBar);
#else
  m_ui->toolBar->setVisible(false);
#endif
}

//--------------------------------------
void MainWindow::onShowFullscreenToggled(bool showFullscreen) {
  QSettings().setValue("interface/showFullscreen", showFullscreen);
  if (showFullscreen)
    this->showFullScreen();
  else
    this->showNormal();
}

//--------------------------------------
void MainWindow::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason) {
  if (reason != QSystemTrayIcon::Context)
    restoreWindow();
}

//--------------------------------------
void MainWindow::restoreGeometryAndState() {
  restoreGeometry(QSettings().value("interface/windowGeometry").toByteArray());
  restoreState(QSettings().value("interface/windowState").toByteArray());
#ifndef Q_OS_MACX
  m_ui->toolBar->setVisible(
      QSettings().value("interface/toolBarVisible", true).toBool());
#else
  m_ui->toolBar->setVisible(false);
#endif
  m_ui->menuBar->setVisible(
      QSettings().value("interface/menuVisible", false).toBool());
}

//--------------------------------------
void MainWindow::saveGeometryAndState() {
  QSettings().setValue("interface/windowGeometry", saveGeometry());
  QSettings().setValue("interface/windowState", saveState(VERSION_MAJOR));
}

//--------------------------------------
void MainWindow::setInfoLabelText(const QString &text) {
  if (m_lblSongInfo)
    m_lblSongInfo->setText(text);
}

//--------------------------------------
Ui::MainWindow *MainWindow::ui() const { return m_ui; }

//--------------------------------------
void MainWindow::registerController(const QString &name,
                                    BaseController *controller) {
  if (!m_controllers.contains(name)) {
    m_controllers.insert(name, controller);
  } else {
    qWarning() << tr("Controller %1 already registered").arg(name);
  }
}

//--------------------------------------
BaseController *MainWindow::controller(const QString &name) const {
  if (m_controllers.contains(name)) {
    return m_controllers.value(name);
  }
  return nullptr;
}

//--------------------------------------
PlayerController *MainWindow::player() const {
  BaseController* c = controller("player");
  if(c != nullptr)
    return qobject_cast<PlayerController *>(c);
  return nullptr;
}

//--------------------------------------
StreamingServicesController *MainWindow::services() const {
  BaseController* c = controller("services");
  if(c != nullptr)
    return qobject_cast<StreamingServicesController *>(c);
  return nullptr;
}

//--------------------------------------
QSystemTrayIcon *MainWindow::trayIcon() const { return m_trayIcon; }

//--------------------------------------
void MainWindow::onPageChanged(int pageIndex) {
  switch (pageIndex) {
  case PAGE_HOME:
    m_ui->menuBar->setVisible(false);
    m_ui->toolBar->setVisible(false);
    break;
  case PAGE_WEB:
    m_ui->menuBar->setVisible(
        QSettings().value("interface/menuVisible", false).toBool());
    m_ui->toolBar->setVisible(
        QSettings().value("interface/toolBarVisible", true).toBool());
    break;
  default:
    break;
  }
}

//--------------------------------------
void MainWindow::setupDockMenu() {
#ifdef Q_OS_MACX
  QMenu *mnu = new QMenu(this);
  mnu->addAction(m_ui->actionPlayPause);
  mnu->addAction(m_ui->actionNext);
  mnu->addAction(m_ui->actionPrevious);
  mnu->addAction(m_ui->actionAdd_to_favorites);
  qt_mac_set_dock_menu(mnu);
#endif
}

//--------------------------------------
void MainWindow::setupToolbar() {
  // label for song infos
  m_lblSongInfo = new QLabel(this);
  m_lblSongInfo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  m_lblSongInfo->setAlignment(Qt::AlignCenter);
  m_ui->toolBar->insertWidget(m_ui->actionPrevious, m_lblSongInfo);

  // Configure drop down menu
#ifndef Q_OS_MAC
  m_ui->toolBar->addSeparator();
  m_BtMenu = new QToolButton(this);
  m_BtMenu->setText(tr("Control"));
  m_BtMenu->setIcon(Icons::configure());
  m_BtMenu->setPopupMode(QToolButton::InstantPopup);
  m_BtMenu->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
  QMenu *mnu = new QMenu(tr("Control"), m_BtMenu);
  mnu->addAction(m_ui->actionShow_menu);
  mnu->addAction(m_ui->actionShow_toolbar);
  mnu->addAction(m_ui->actionFullscreen);
  mnu->addSeparator();
  mnu->addAction(m_ui->actionSelect_service);
  mnu->addAction(m_ui->actionPreferences);

  QMenu *mnuHelp = mnu->addMenu("Help");
  mnuHelp->addActions(m_ui->menuHelp->actions());
  mnuHelp->setIcon(Icons::help());

  mnu->addAction(m_ui->actionQuit);
  m_BtMenu->setMenu(mnu);
  m_ui->toolBar->addWidget(m_BtMenu);
#endif
}
