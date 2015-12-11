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

#ifndef WEBVIEW_H
#define WEBVIEW_H

//---------------------------------------------------------
// Headers
//---------------------------------------------------------
#include <QWebEngineView>
#include <QWebEnginePage>

//---------------------------------------------------------
// Classes
//---------------------------------------------------------
/*!
 * \brief The WebView class extends QWebView to add support for
 * JavaScript popup windows (e.g. for signing in with google,
 * twitter or facebook)
 */
class WebView : public QWebEngineView {
public:
  explicit WebView(QWidget *parent = NULL);

  void load(const QUrl &url);
  void deleteAllCookies();

protected:
  virtual QWebEngineView *createWindow(QWebEnginePage::WebWindowType type);
};

class WebPage : public QWebEnginePage {
public:
  explicit WebPage(QObject *parent);
  bool
  certificateError(const QWebEngineCertificateError &certificateError) override;
};

#endif // WEBVIEW_H
