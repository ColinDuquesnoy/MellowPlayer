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
#include <mellowplayer.h>
#include "cookiejar.h"
#include "dlgselectservice.h"
#include "dlgpreferences.h"
#include "icons.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "shortcuts.h"

#define PAGE_HOME 0
#define PAGE_WEB 1

//---------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->ui->setupUi(this);
    this->setupActions();
    this->setupIcons();
    this->restoreGeometryAndState();
    this->setupWebView();
    this->setupUpdateTimer();
    this->setupTrayIcon();
    this->connectSlots();
    this->ui->menuView->addActions(this->createPopupMenu()->actions());
}

//---------------------------------------------------------
MainWindow::~MainWindow()
{
    delete ui;
}

//---------------------------------------------------------
void MainWindow::showWebPage()
{
    this->ui->stackedWidget->setCurrentIndex(PAGE_WEB);
    this->ui->menubar->show();
}

//---------------------------------------------------------
void MainWindow::showHomePage()
{
    this->ui->stackedWidget->setCurrentIndex(PAGE_HOME);
    this->ui->menubar->hide();
}

//---------------------------------------------------------
void MainWindow::onLinkClicked(QUrl url)
{
    IStreamingService* sv = Services::streamingServices()->currentService();
    if( sv && url.toString().contains(sv->url().toString()))
        this->ui->webView->load(url);
    else
        QDesktopServices::openUrl(url);
}

//---------------------------------------------------------
void MainWindow::onPlayPauseTriggered()
{
    Services::player()->playPause();
}

//---------------------------------------------------------
void MainWindow::onStopTriggered()
{
    Services::player()->stop();
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
        this->show();
}

//---------------------------------------------------------
void MainWindow::onSelectServiceTriggered()
{
    this->show();
    QString service = DlgSelectServices::selectService(this);
    if(service != "")
    {
        if(Services::streamingServices()->startService(service))
        {
            this->showWebPage();
            QSettings().setValue("service", service);
        }
    }
}

//---------------------------------------------------------
void MainWindow::onPreferencesTriggered()
{
    this->show();
    DlgPreferences::editPreferences(this);
}

//---------------------------------------------------------
void MainWindow::closeEvent(QCloseEvent *event)
{
    bool minimizeToTray = QSettings().value(
        "minimizeToTray", QVariant(true)).toBool();
    if(this->isVisible() && minimizeToTray &&
        this->ui->stackedWidget->currentIndex() == PAGE_WEB)
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
        this->hide();
        event->ignore();
    }
    else
        // no service is running or the window is already hidden,
        // quit application
        qApp->exit(0);
}

//---------------------------------------------------------
void MainWindow::setupIcons()
{
    this->ui->actionSelect_service->setIcon(Icons::selectStreamingService());
    this->ui->actionPreferences->setIcon(Icons::preferences());
    this->ui->actionQuit->setIcon(Icons::quit());

    this->ui->actionPlayPause->setIcon(Icons::play());
    this->ui->actionStop->setIcon(Icons::stop());
    this->ui->actionNext->setIcon(Icons::next());
    this->ui->actionPrevious->setIcon(Icons::previous());

    this->ui->actionAbout_MellowPlayer->setIcon(Icons::about());
    this->ui->actionReport_a_bug->setIcon(Icons::reportBug());

    this->ui->pushButtonSelect->setIcon(Icons::selectStreamingService());
    this->ui->pushButtonPreferences->setIcon(Icons::preferences());
    this->ui->pushButtonQuit->setIcon(Icons::quit());
}

//---------------------------------------------------------
void MainWindow::setupActions()
{
    QString defaults[] = {
        DEFAULT_SHORTCUT_PLAY,
        DEFAULT_SHORTCUT_STOP,
        DEFAULT_SHORTCUT_NEXT,
        DEFAULT_SHORTCUT_PREVIOUS
    };
    QAction* actions[] = {
        this->ui->actionPlayPause,
        this->ui->actionStop,
        this->ui->actionNext,
        this->ui->actionPrevious
    };
    for(int i = 0; i < 4; ++i){
        QAction* a = actions[i];
        this->addAction(a);
        a->setShortcut(QSettings().value(
            a->objectName(), defaults[i]).toString());
    }

    // setup roles, this is only for OS X
    ui->actionPreferences->setMenuRole(QAction::PreferencesRole);
    ui->actionSelect_service->setMenuRole(QAction::ApplicationSpecificRole);
    ui->actionQuit->setMenuRole(QAction::QuitRole);
    ui->actionAbout_MellowPlayer->setMenuRole(QAction::AboutRole);
    ui->actionAbout_Qt->setMenuRole(QAction::AboutQtRole);
}

//---------------------------------------------------------
void MainWindow::setupTrayIcon()
{
    this->trayIcon = new TrayIcon(this);

    QMenu* mnu = new QMenu();
    mnu->addAction(this->ui->actionRestoreWindow);
    mnu->addSeparator();
    mnu->addAction(this->ui->actionPlayPause);
    mnu->addAction(this->ui->actionStop);
    mnu->addAction(this->ui->actionNext);
    mnu->addAction(this->ui->actionPrevious);
    mnu->addSeparator();
    mnu->addAction(this->ui->actionSelect_service);
    mnu->addAction(this->ui->actionPreferences);
    mnu->addSeparator();
#ifndef __kde_support__
    // kde provides a quit action automatically.
    mnu->addAction(this->ui->actionQuit);
#endif
    this->trayIcon->setContextMenu(mnu);

    this->trayIcon->setIcon(Icons::mellowPlayer());
    this->connect(this->trayIcon, SIGNAL(activated(bool)),
                  this, SLOT(onTrayIconActivated(bool)));
    Services::_setTrayIcon(this->trayIcon);
}

//---------------------------------------------------------
void MainWindow::setupUpdateTimer()
{
    this->updateTimer = new QTimer(this);
    this->updateTimer->setInterval(10);
    this->connect(this->updateTimer, SIGNAL(timeout()),
                  this, SLOT(updatePlayer()));
    this->updateTimer->start();
}

//---------------------------------------------------------
void MainWindow::setupWebView()
{
    // Setup web view
    ui->webView->page()->networkAccessManager()->setCookieJar(
                new CookieJar(ui->webView));
    // make sure javascript and flash are enabled.
    QWebSettings* settings = this->ui->webView->settings();
    settings->setAttribute(QWebSettings::JavascriptEnabled, true);
    settings->setAttribute(QWebSettings::PluginsEnabled, true);
#ifdef QT_DEBUG
    settings->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
#endif
    // handle opening links ourself so that we open external links in an
    // external browser
    this->ui->webView->page()->setLinkDelegationPolicy(
                QWebPage::DelegateAllLinks);
    Services::_setWebView(ui->webView);
}

//---------------------------------------------------------
void MainWindow::connectSlots()
{
    this->connect(this->ui->webView, SIGNAL(linkClicked(QUrl)),
                  this, SLOT(onLinkClicked(QUrl)));
    this->connect(this->ui->actionPlayPause, SIGNAL(triggered()),
                  this, SLOT(onPlayPauseTriggered()));
    this->connect(this->ui->actionStop, SIGNAL(triggered()),
                  this, SLOT(onStopTriggered()));
    this->connect(this->ui->actionNext, SIGNAL(triggered()),
                  this, SLOT(onNextTriggered()));
    this->connect(this->ui->actionPrevious, SIGNAL(triggered()),
                  this, SLOT(onPreviousTriggered()));

    this->connect(this->ui->actionRestoreWindow, SIGNAL(triggered()),
                  this, SLOT(show()));

    this->connect(this->ui->actionSelect_service, SIGNAL(triggered()),
                  this, SLOT(onSelectServiceTriggered()));
    this->connect(this->ui->pushButtonSelect, SIGNAL(clicked()),
                  this, SLOT(onSelectServiceTriggered()));

    this->connect(this->ui->actionPreferences, SIGNAL(triggered()),
                  this, SLOT(onPreferencesTriggered()));
    this->connect(this->ui->pushButtonPreferences, SIGNAL(clicked()),
                  this, SLOT(onPreferencesTriggered()));

    this->connect(this->ui->actionQuit, SIGNAL(triggered()),
                  this, SLOT(quit()));
    this->connect(this->ui->pushButtonQuit, SIGNAL(clicked()),
                  this, SLOT(quit()));

    this->connect(this->ui->actionAbout_MellowPlayer, SIGNAL(triggered()),
                  this, SLOT(onAboutTriggered()));
    this->connect(this->ui->actionAbout_Qt, SIGNAL(triggered()),
                  this, SLOT(onAboutQtTriggered()));
    this->connect(this->ui->actionReport_a_bug, SIGNAL(triggered()),
                  this, SLOT(onReportBugTriggered()));
}

//---------------------------------------------------------
void MainWindow::updatePlayer()
{
    PlayerInterface* player = Services::player();
    SongInfo song = player->update();
    if(song.isValid())
    {
        this->setWindowTitle(QString("%1 - MellowPlayer").arg(song.toString()));
        this->trayIcon->setToolTip(QString("%1 - MellowPlayer").arg(
            song.toString()));
        this->ui->actionNext->setEnabled(true);
        this->ui->actionPrevious->setEnabled(true);
        this->ui->actionStop->setEnabled(player->playbackStatus() != Stopped);
        this->ui->actionPlayPause->setEnabled(true);
        if(player->playbackStatus() == Paused)
        {
            this->ui->actionPlayPause->setIcon(Icons::play());
            this->ui->actionPlayPause->setText(tr("Play"));
        }
        else if(player->playbackStatus() == Playing)
        {
            this->ui->actionPlayPause->setIcon(Icons::pause());
            this->ui->actionPlayPause->setText(tr("Pause"));
        }
    }
    else
    {
        this->setWindowTitle("MellowPlayer");
        this->ui->actionNext->setEnabled(false);
        this->ui->actionPrevious->setEnabled(false);
        this->ui->actionStop->setEnabled(false);
        this->ui->actionPlayPause->setEnabled(false);
        if(ui->actionPlayPause->text() != tr("Play"))
        {
            this->ui->actionPlayPause->setText(QApplication::translate("MainWindow", "Play", 0));
            this->ui->actionPlayPause->setIcon(Icons::play());
        }
        this->trayIcon->setToolTip("MellowPlayer");
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
    this->show();
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
        "PARTICULAR PURPOSE.<br/>")
        .arg(version, QLatin1String(__DATE__), QLatin1String(__TIME__),
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
void MainWindow::onReportBugTriggered()
{
    QDesktopServices::openUrl(QUrl(
        "https://github.com/ColinDuquesnoy/MellowPlayer/issues/new"));
}

//---------------------------------------------------------
void MainWindow::quit()
{
    bool confirm = QSettings().value("confirmQuit", true).toBool();
    if(!confirm || QMessageBox::question(this, tr("Confirm quit"),
                       tr("Are you sure you want to exit MellowPlayer?"),
                       QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) ==
       QMessageBox::Yes)
    {
        qApp->exit();
    }
}

//---------------------------------------------------------
void MainWindow::restoreGeometryAndState()
{
    this->restoreGeometry(QSettings().value("windowGeometry").toByteArray());
    this->restoreState(QSettings().value("windowState").toByteArray());
    this->ui->toolBar->setVisible(
        QSettings().value("toolbarVisible", false).toBool());
}

//---------------------------------------------------------
void MainWindow::saveGeometryAndState()
{
    QSettings().setValue("windowGeometry", this->saveGeometry());
    QSettings().setValue("windowState", this->saveState(VERSION_MAJOR));


    // store toolbar state
    foreach(QAction* action, this->ui->menuView->actions())
    {
        QString text = action->text();
        QString oName = this->ui->toolBar->objectName();
        if(text.remove("&").toLower() == oName.toLower())
        {
            QSettings().setValue("toolbarVisible", action->isChecked());
        }
    }
}
