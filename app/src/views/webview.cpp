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
#include <QWebEngineCookieStore>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include <QWebEngineView>
#include "views/webview.h"

//---------------------------------------------------------
// Implementations
//---------------------------------------------------------
//-------------------------------------
WebView::WebView(QWidget *parent) : QWebEngineView(parent) {}

//-------------------------------------
void WebView::load(const QUrl &url) {

  qDebug() << "Loading" << url.toString();
  WebPage *page = new WebPage(this);
  page->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
  page->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
  page->settings()->setAttribute(QWebEngineSettings::JavascriptCanOpenWindows,
                                 true);
  page->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
  setPage(page);
  page->load(url);

  qDebug() << page->profile()->cachePath();
}

//-------------------------------------
void WebView::deleteAllCookies() {
  QWebEngineCookieStore *cookieStore = this->page()->profile()->cookieStore();
  if (cookieStore) {
    qDebug() << "cookie store found";
    cookieStore->deleteAllCookies();
  } else
    qDebug() << "cookie store NOT found";
}

//-------------------------------------
QWebEngineView *WebView::createWindow(QWebEnginePage::WebWindowType type) {
  Q_UNUSED(type);

  QWebEngineView *webView = new QWebEngineView();
  QWebEnginePage *newWeb = new QWebEnginePage(webView);
  connect(newWeb, SIGNAL(windowCloseRequested()), webView, SLOT(close()));
  webView->setPage(newWeb);
  webView->show();
  return webView;
}

//-------------------------------------
WebPage::WebPage(QObject *parent) : QWebEnginePage(parent) {}

//-------------------------------------
bool WebPage::certificateError(
    const QWebEngineCertificateError &certificateError) {
  // ignore certificate errors
  Q_UNUSED(certificateError);
  return true;
}
