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
    loadPlugins();

    connect(this->ui->webView, &QWebView::linkClicked, this,
            &MainWindow::onLinkClicked);
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
