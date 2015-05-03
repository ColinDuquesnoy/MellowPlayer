//---------------------------------------------------------
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
//---------------------------------------------------------

#include <QDesktopServices>
#include <QMessageBox>
#include <QWebFrame>
#include <mellowplayer.h>
#include "dlgselectservice.h"
#include "dlgpreferences.h"
#include "icons.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shortcuts.h"

#define PAGE_HOME 0
#define PAGE_WEB 1

//---------------------------------------------------------
MainWindow::MainWindow(bool debug, QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    setupActions();
    setupIcons();
    restoreGeometryAndState();
    setupWebView(debug);
    setupUpdateTimer();
    setupTrayIcon();
    setupDockMenu();
    connectSlots();
    m_ui->menuView->addActions(createPopupMenu()->actions());
    setupQuikLists();
}

//---------------------------------------------------------
MainWindow::~MainWindow()
{
    delete m_ui;
}

//---------------------------------------------------------
void MainWindow::showWebPage()
{
    m_ui->stackedWidget->setCurrentIndex(PAGE_WEB);
#ifndef __unity_support__
    m_ui->menubar->show();
#endif
    m_updateTimer->stop();
}

//---------------------------------------------------------
void MainWindow::showHomePage()
{
    m_ui->stackedWidget->setCurrentIndex(PAGE_HOME);
#ifndef __unity_support__
    m_ui->menubar->hide();
#endif
}

//---------------------------------------------------------
void MainWindow::onLinkClicked(QUrl url)
{
    IStreamingService* sv = Services::streamingServices()->currentService();
    if( sv && url.toString().contains(sv->url().toString()))
        m_ui->webView->load(url);
    else
        QDesktopServices::openUrl(url);
}

//---------------------------------------------------------
void MainWindow::onPlayPauseTriggered()
{
    Services::player()->playPause();
}

//---------------------------------------------------------
void MainWindow::onNextTriggered()
{
    Services::player()->next();
}

//---------------------------------------------------------
void MainWindow::onPreviousTriggered()
{
    Services::player()->previous();
}

//---------------------------------------------------------
void MainWindow::onTrayIconActivated(bool active)
{
    if(active)
        show();
#ifdef __unity_support__
    m_ui->menubar->show();
#endif
}

//---------------------------------------------------------
void MainWindow::onSelectServiceTriggered()
{
    restoreWindow();
    QString service = DlgSelectServices::selectService(this);
    if(service != "")
    {
        QSettings().setValue("service", service);
        if(Services::streamingServices()->startService(service))
            showWebPage();
        else
            showHomePage();
    }
}

//---------------------------------------------------------
void MainWindow::onPreferencesTriggered()
{
    restoreWindow();
    DlgPreferences::editPreferences(this);
}

//---------------------------------------------------------
void MainWindow::closeEvent(QCloseEvent *event)
{
#if defined(Q_OS_MACX) || defined(__unity_support__)
    Q_UNUSED(event);
    if(!exitApplication())
        event->ignore();
#else
    bool minimizeToTray = QSettings().value(
        "minimizeToTray", QVariant(true)).toBool();
    if(isVisible() && minimizeToTray &&
        m_ui->stackedWidget->currentIndex() == PAGE_WEB)
    {
        bool showMsg = QSettings().value(
            "showMinimizeToTrayMsg", true).toBool();
        if(showMsg)
        {
            QMessageBox::information(
                this, tr("Minimizing to system tray"),
                tr("The program will keep running in the system tray. To terminate "
                "the program, choose <b>Quit</b> in the context menu of the "
                "system tray entry."));
            QSettings().setValue("showMinimizeToTrayMsg", false);
        }
        hide();
        event->ignore();
    }
    else
        // no service is running or the window is already hidden,
        // quit application
        qApp->exit(0);
#endif
}

//---------------------------------------------------------
void MainWindow::setupIcons()
{
    m_ui->actionSelect_service->setIcon(Icons::selectStreamingService());
    m_ui->actionPreferences->setIcon(Icons::preferences());
    m_ui->actionQuit->setIcon(Icons::quit());

    m_ui->actionPlayPause->setIcon(Icons::play());
    m_ui->actionNext->setIcon(Icons::next());
    m_ui->actionPrevious->setIcon(Icons::previous());
    m_ui->actionAdd_to_favorites->setIcon(Icons::favorite());

    m_ui->actionAbout_MellowPlayer->setIcon(Icons::about());
    m_ui->actionReport_a_bug->setIcon(Icons::reportBug());

    m_ui->pushButtonSelect->setIcon(Icons::selectStreamingService());
    m_ui->pushButtonPreferences->setIcon(Icons::preferences());
    m_ui->pushButtonQuit->setIcon(Icons::quit());
}

//---------------------------------------------------------
void MainWindow::setupActions()
{
    QString defaults[] = {
        DEFAULT_SHORTCUT_PLAY,
        DEFAULT_SHORTCUT_NEXT,
        DEFAULT_SHORTCUT_PREVIOUS,
        DEFAULT_SHORTCUT_FAVORITE
    };
    QAction* actions[] = {
        m_ui->actionPlayPause,
        m_ui->actionNext,
        m_ui->actionPrevious,
        m_ui->actionAdd_to_favorites
    };
    for(int i = 0; i < 4; ++i){
        QAction* a = actions[i];
        addAction(a);
        a->setShortcut(QSettings().value(
            a->objectName(), defaults[i]).toString());
    }

    // setup roles, this is only for OS X
    m_ui->actionPreferences->setMenuRole(QAction::PreferencesRole);
    m_ui->actionSelect_service->setMenuRole(QAction::ApplicationSpecificRole);
    m_ui->actionQuit->setMenuRole(QAction::QuitRole);
    m_ui->actionAbout_MellowPlayer->setMenuRole(QAction::AboutRole);
    m_ui->actionAbout_Qt->setMenuRole(QAction::AboutQtRole);
}

//---------------------------------------------------------
void MainWindow::setupTrayIcon()
{
    m_trayIcon = new TrayIcon(this);

    QMenu* mnu = new QMenu();
    mnu->addAction(m_ui->actionRestoreWindow);
    mnu->addSeparator();
    mnu->addAction(m_ui->actionPlayPause);
    mnu->addAction(m_ui->actionNext);
    mnu->addAction(m_ui->actionPrevious);
    mnu->addAction(m_ui->actionAdd_to_favorites);
    mnu->addSeparator();
    mnu->addAction(m_ui->actionSelect_service);
    mnu->addAction(m_ui->actionPreferences);
    mnu->addSeparator();
#ifndef __kde_support__
    // kde provides a quit action automatically.
    mnu->addAction(m_ui->actionQuit);
#endif
    m_trayIcon->setContextMenu(mnu);

    m_trayIcon->setIcon(Icons::mellowPlayer());
    connect(m_trayIcon, SIGNAL(activated(bool)),
                  this, SLOT(onTrayIconActivated(bool)));
    Services::_setTrayIcon(m_trayIcon);
}

//---------------------------------------------------------
void MainWindow::setupUpdateTimer()
{
    m_updateTimer = new QTimer(this);
    m_updateTimer->setInterval(100);
    connect(m_updateTimer, SIGNAL(timeout()),
                  this, SLOT(updatePlayer()));
}

//---------------------------------------------------------
void MainWindow::setupWebView(bool debug)
{
    // make sure javascript and flash are enabled.
    QWebSettings* settings = m_ui->webView->settings();
    settings->setAttribute(QWebSettings::JavascriptEnabled, true);
    settings->setAttribute(QWebSettings::PluginsEnabled, true);
    if(debug)
        settings->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

    // handle opening links ourself so that we open external links in an
    // external browser
    m_ui->webView->page()->setLinkDelegationPolicy(
                QWebPage::DelegateAllLinks);
    Services::_setWebView(m_ui->webView);
    qDebug() << "Has flash: " << Services::hasFlash();
}

//---------------------------------------------------------
void MainWindow::connectSlots()
{
    connect(m_ui->webView, SIGNAL(linkClicked(QUrl)),
                  this, SLOT(onLinkClicked(QUrl)));
    connect(m_ui->actionPlayPause, SIGNAL(triggered()),
                  this, SLOT(onPlayPauseTriggered()));
    connect(m_ui->actionNext, SIGNAL(triggered()),
                  this, SLOT(onNextTriggered()));
    connect(m_ui->actionPrevious, SIGNAL(triggered()),
                  this, SLOT(onPreviousTriggered()));

    connect(m_ui->actionRestoreWindow, SIGNAL(triggered()),
                  this, SLOT(restoreWindow()));

    connect(m_ui->actionSelect_service, SIGNAL(triggered()),
                  this, SLOT(onSelectServiceTriggered()));
    connect(m_ui->pushButtonSelect, SIGNAL(clicked()),
                  this, SLOT(onSelectServiceTriggered()));

    connect(m_ui->actionPreferences, SIGNAL(triggered()),
                  this, SLOT(onPreferencesTriggered()));
    connect(m_ui->pushButtonPreferences, SIGNAL(clicked()),
                  this, SLOT(onPreferencesTriggered()));

    connect(m_ui->actionQuit, SIGNAL(triggered()),
                  this, SLOT(exitApplication()));
    connect(m_ui->pushButtonQuit, SIGNAL(clicked()),
                  this, SLOT(exitApplication()));

    connect(m_ui->actionAbout_MellowPlayer, SIGNAL(triggered()),
                  this, SLOT(onAboutTriggered()));
    connect(m_ui->actionAbout_Qt, SIGNAL(triggered()),
                  this, SLOT(onAboutQtTriggered()));
    connect(m_ui->actionReport_a_bug, SIGNAL(triggered()),
                  this, SLOT(onReportBugTriggered()));
    connect(m_ui->actionWiki, SIGNAL(triggered()),
            this, SLOT(onWikiTriggered()));
    connect(m_ui->actionAdd_to_favorites, SIGNAL(triggered()),
                  this, SLOT(onAddToFavorites()));

    connect(m_ui->webView, SIGNAL(loadStarted()),
            this, SLOT(onLoadStarted()));
    connect(m_ui->webView, SIGNAL(loadFinished(bool)),
            this, SLOT(onLoadFinished(bool)));
}

//---------------------------------------------------------
void MainWindow::updatePlayer()
{
    PlayerInterface* player = Services::player();
    SongInfo song = player->update();
    m_ui->actionAdd_to_favorites->setVisible(
        player->canFavorite() && player->currentSong().isValid());
    m_ui->actionAdd_to_favorites->setText(
        player->isFavorite() ? tr("Remove from favorites") :
                               tr("Add to favorites"));
    if(song.isValid())
    {
        setWindowTitle(QString("%1 - %2 - MellowPlayer").arg(
            song.toString(),
            Services::streamingServices()->currentService()->metaData().name));
        m_trayIcon->setToolTip(QString("%1 - MellowPlayer").arg(
            song.toString()));
        m_ui->actionNext->setEnabled(player->canGoNext());
        m_ui->actionPrevious->setEnabled(player->canGoPrevious());
        m_ui->actionPlayPause->setEnabled(true);
        if(player->playbackStatus() == Paused)
        {
            m_ui->actionPlayPause->setIcon(Icons::play());
            m_ui->actionPlayPause->setText(tr("Play"));
        }
        else if(player->playbackStatus() == Playing)
        {
            m_ui->actionPlayPause->setIcon(Icons::pause());
            m_ui->actionPlayPause->setText(tr("Pause"));
        }

        m_ui->actionRestoreWindow->setText(
            Services::streamingServices()->currentService()->metaData().name +
            " - " + song.toString());
    }
    else
    {
        IStreamingService* sv = Services::streamingServices()->currentService();
        if(sv)
            setWindowTitle(QString("%1 - MellowPlayer").arg(sv->metaData().name));
        m_ui->actionNext->setEnabled(false);
        m_ui->actionPrevious->setEnabled(false);
        m_ui->actionPlayPause->setEnabled(false);
        if(m_ui->actionPlayPause->text() != tr("Play"))
        {
            m_ui->actionPlayPause->setText(QApplication::translate("MainWindow", "Play", 0));
            m_ui->actionPlayPause->setIcon(Icons::play());
        }
        m_trayIcon->setToolTip("MellowPlayer");

        m_ui->actionRestoreWindow->setText(
            Services::streamingServices()->currentService()->metaData().name + " - " + tr("Stopped"));
    }
}

//---------------------------------------------------------
static QString compilerString()
{
#if defined(Q_CC_CLANG) // must be before GNU, because clang claims to be GNU too
    QString isAppleString;
#if defined(__apple_build_version__) // Apple clang has other version numbers
    isAppleString = QLatin1String(" (Apple)");
#endif
    return QLatin1String("Clang " ) + QString::number(__clang_major__) + QLatin1Char('.')
            + QString::number(__clang_minor__) + isAppleString;
#elif defined(Q_CC_GNU)
    return QLatin1String("GCC " ) + QLatin1String(__VERSION__);
#elif defined(Q_CC_MSVC)
    if (_MSC_VER >= 1800) // 1800: MSVC 2013 (yearly release cycle)
        return QLatin1String("MSVC ") + QString::number(2008 + ((_MSC_VER / 100) - 13));
    if (_MSC_VER >= 1500) // 1500: MSVC 2008, 1600: MSVC 2010, ... (2-year release cycle)
        return QLatin1String("MSVC ") + QString::number(2008 + 2 * ((_MSC_VER / 100) - 15));
#endif
    return QLatin1String("<unknown compiler>");
}

//---------------------------------------------------------
void MainWindow::onAboutTriggered()
{
    show();
    QString version = QString("%1.%2.%3%4")
            .arg(VERSION_MAJOR)
            .arg(VERSION_MINOR)
            .arg(VERSION_MICRO)
            .arg(VERSION_STATUS);

    const QString description = tr(
        "<h3>MellowPlayer %1</h3>"
        "Built on %2 at %3 (%4, %5 bit)<br/>"
        "<br/>"
        "Copyright 2015 Colin Duquesnoy. All rights reserved.<br/>"
        "<br/>"
        "The program is provided AS IS with NO WARRANTY OF ANY KIND, "
        "INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A "
        "PARTICULAR PURPOSE.<br/><br/>"
#ifndef Q_OS_LINUX
        "<a href=\"http://colinduquesnoy.github.io/MellowPlayer/\">Click here to download the latest version!</a> "
#endif
        ).arg(version, QLatin1String(__DATE__), QLatin1String(__TIME__),
              compilerString(), QString::number(QSysInfo::WordSize));

    QMessageBox::about(
                this, tr("About MellowPlayer"), description);
}

//---------------------------------------------------------
void MainWindow::onAboutQtTriggered()
{
    QMessageBox::aboutQt(this);
}

//---------------------------------------------------------
void MainWindow::onWikiTriggered()
{
    QDesktopServices::openUrl(QUrl(
        "https://github.com/ColinDuquesnoy/MellowPlayer/"
        "wiki#user-documentation"));
}

//---------------------------------------------------------
void MainWindow::onReportBugTriggered()
{
    QDesktopServices::openUrl(QUrl(
        "https://github.com/ColinDuquesnoy/MellowPlayer/issues/new"));
}

//---------------------------------------------------------
bool MainWindow::exitApplication()
{
    bool confirm = QSettings().value("confirmQuit", true).toBool();
    if(confirm)
    {
        int answer = QMessageBox::question(
            this, tr("Confirm quit"),
            tr("Are you sure you want to exit MellowPlayer?"),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
       if(answer == QMessageBox::No)
           return false;
    }
    qApp->exit();
    return true;
}

//---------------------------------------------------------
void MainWindow::onAddToFavorites()
{
    Services::player()->addToFavorites();
}

//---------------------------------------------------------
void MainWindow::onLoadFinished(bool ok)
{
    if(ok)
    {
        QWebFrame* frame = m_ui->webView->page()->mainFrame();
        bool jqueryMissing = frame->evaluateJavaScript("!window.jQuery").toBool();
        if(jqueryMissing)
        {
            QString pth(":/jquery-2.1.3.min.js");
            qDebug() << "injecting " << pth;
            QFile f(pth);
            if(f.open(QFile::ReadOnly|QIODevice::Text))
            {
                frame->evaluateJavaScript(f.readAll());
            }
        }
        m_updateTimer->start();
    }
}

//---------------------------------------------------------
void MainWindow::onLoadStarted()
{
    m_ui->actionRestoreWindow->setText(
        Services::streamingServices()->currentService()->metaData().name + " - " + tr("Loading"));
}

//---------------------------------------------------------
void MainWindow::restoreWindow()
{
    Services::raiseMainWindow();
}

//---------------------------------------------------------
void MainWindow::restoreGeometryAndState()
{
    restoreGeometry(QSettings().value("windowGeometry").toByteArray());
    restoreState(QSettings().value("windowState").toByteArray());
    m_ui->toolBar->setVisible(
        QSettings().value("toolbarVisible", false).toBool());
}

//---------------------------------------------------------
void MainWindow::saveGeometryAndState()
{
    QSettings().setValue("windowGeometry", saveGeometry());
    QSettings().setValue("windowState", saveState(VERSION_MAJOR));


    // store toolbar state
    foreach(QAction* action, m_ui->menuView->actions())
    {
        QString text = action->text();
        QString oName = m_ui->toolBar->objectName();
        if(text.remove("&").toLower() == oName.toLower())
        {
            QSettings().setValue("toolbarVisible", action->isChecked());
        }
    }
}

//---------------------------------------------------------
void MainWindow::setupQuikLists()
{
#ifdef __unity_support__
    QDBusMessage signal = QDBusMessage::createSignal("/",
        "com.canonical.Unity.LauncherEntry", "Update");

    //set the application ID
    signal << "application://mellowplayer.desktop";

    //set the properties
    QVariantMap properties;

    QString dbusPath = "/com/me/mellowplayer/quicklist";

    m_quickList = new QMenu();
    m_quickList->addAction(m_ui->actionRestoreWindow);
    m_quickList->addSeparator();
    m_quickList->addAction(m_ui->actionPlayPause);
    m_quickList->addAction(m_ui->actionNext);
    m_quickList->addAction(m_ui->actionPrevious);
    m_quickList->addAction(m_ui->actionAdd_to_favorites);
    m_quickList->addSeparator();
    m_quickList->addAction(m_ui->actionSelect_service);
    m_quickList->addAction(m_ui->actionPreferences);
    exporter = new DBusMenuExporter(dbusPath, m_quickList);

    properties["quicklist"] = dbusPath;

    signal << properties;

    //send the signal
    QDBusConnection::sessionBus().send(signal);
#endif
}

void MainWindow::setupDockMenu()
{
#ifdef Q_OS_MACX
    QMenu* mnu = new QMenu(this);
    mnu->addAction(m_ui->actionPlayPause);
    mnu->addAction(m_ui->actionNext);
    mnu->addAction(m_ui->actionPrevious);
    mnu->addAction(m_ui->actionAdd_to_favorites);
    qt_mac_set_dock_menu(mnu);
#endif
}
