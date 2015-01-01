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

#include "cookiejar.h"
#include "mainwindow.h"
#include "mellowplayer.h"
#include "pluginmanager.h"
#include "ui_mainwindow.h"

#define PAGE_HOME 0
#define PAGE_WEB 1

//---------------------------------------------------------
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionSelect_service->setMenuRole(QAction::ApplicationSpecificRole);
    this->setupWebView();
    loadPlugins();
    this->connectSlots();
    this->setupUpdateTimer();
    this->setupTrayIcon();
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
    ICloudMusicService* sv = Services::cloudServices()->currentService();
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
void MainWindow::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::DoubleClick)
        this->show();
}

//---------------------------------------------------------
void MainWindow::closeEvent(QCloseEvent *event)
{
    bool minimizeToTray = QSettings().value(
        "minimizeToTray", QVariant(true)).toBool();
    if(this->isVisible() && minimizeToTray)
    {
        bool showMsg = QSettings().value(
            "showMinimizeToTrayMsg", true).toBool();
        if(showMsg)
        {
            QMessageBox::information(
                this, "MellowPlayer",
                "The program will keep running in the system tray. To terminate "
                "the program, choose <b>Quit</b> in the context menu of the "
                "system tray entry.");
            QSettings().setValue("showMinimizeToTrayMsg", false);
        }
        this->hide();
        event->ignore();
    }
    else
    {
        this->updateTimer->stop();
        this->trayIcon->hide();
        event->accept();
    }
}

//---------------------------------------------------------
void MainWindow::setupTrayIcon()
{
    this->trayIcon = new QSystemTrayIcon(this);
    this->trayIcon->setIcon(this->windowIcon());

    QMenu* mnu = new QMenu();
    mnu->addAction(this->ui->actionPlayPause);
    mnu->addAction(this->ui->actionStop);
    mnu->addAction(this->ui->actionNext);
    mnu->addAction(this->ui->actionPrevious);
    mnu->addSeparator();
    mnu->addAction(this->ui->actionSelect_service);
    mnu->addAction(this->ui->actionPreferences);
    mnu->addSeparator();
    mnu->addAction(this->ui->actionAbout_MellowPlayer);
    mnu->addAction(this->ui->actionReport_a_bug);
    mnu->addSeparator();
//#ifndef __kde_support__
    // kde provides a quit action automatically.
    mnu->addAction(this->ui->actionQuit);
//#endif
    this->trayIcon->setContextMenu(mnu);

    this->trayIcon->show();
    this->connect(this->trayIcon, &QSystemTrayIcon::activated,
                  this, &MainWindow::onTrayIconActivated);
}


//---------------------------------------------------------
void MainWindow::setupUpdateTimer()
{
    this->updateTimer = new QTimer(this);
    this->updateTimer->setInterval(500);
    this->connect(this->updateTimer, &QTimer::timeout,
                  this, &MainWindow::updatePlayer);
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
    // handle opening links ourself so that we open external links in an
    // external browser
    this->ui->webView->page()->setLinkDelegationPolicy(
                QWebPage::DelegateAllLinks);
    Services::_setWebView(ui->webView);
}

//---------------------------------------------------------
void MainWindow::connectSlots()
{
    this->connect(this->ui->webView, &QWebView::linkClicked,
                  this, &MainWindow::onLinkClicked);
    this->connect(this->ui->actionPlayPause, &QAction::triggered,
                  this, &MainWindow::onPlayPauseTriggered);
    this->connect(this->ui->actionStop, &QAction::triggered,
                  this, &MainWindow::onStopTriggered);
    this->connect(this->ui->actionNext, &QAction::triggered,
                  this, &MainWindow::onNextTriggered);
    this->connect(this->ui->actionPrevious, &QAction::triggered,
                  this, &MainWindow::onPreviousTriggered);
    this->connect(this->ui->actionQuit, &QAction::triggered,
                  qApp, &QApplication::quit);
}

//---------------------------------------------------------
void MainWindow::updatePlayer()
{
    SongInfo song = Services::player()->update();
    if(song.isValid())
    {
        this->setWindowTitle(QString("%1 - MellowPlayer").arg(song.songName));
        this->ui->actionNext->setEnabled(true);
        this->ui->actionPrevious->setEnabled(true);
        this->ui->actionStop->setEnabled(song.playbackStatus != Stopped);
        this->ui->actionPlayPause->setEnabled(true);
        this->ui->actionPlayPause->setText(song.songName);
        if(song.playbackStatus == Paused)
            this->ui->actionPlayPause->setIcon(
                QIcon(":/icons/media-playback-start.png"));
        else if(song.playbackStatus == Playing)
            this->ui->actionPlayPause->setIcon(
                QIcon(":/icons/media-playback-pause.png"));
        else if(song.playbackStatus == Loading)
          this->ui->actionPlayPause->setIcon(
                QIcon(":/icons/loading_static.png"));
    }
    else
    {
        this->setWindowTitle("MellowPlayer");
        this->ui->actionNext->setEnabled(false);
        this->ui->actionPrevious->setEnabled(false);
        this->ui->actionStop->setEnabled(false);
        this->ui->actionPlayPause->setEnabled(false);
        this->ui->actionPlayPause->setText("Play/Pause");
        this->ui->actionPlayPause->setIcon(
            QIcon(":/icons/media-playback-start.png"));
    }
}
