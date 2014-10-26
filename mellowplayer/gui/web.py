"""
This module contains the webview and the cookie jar used by the main window.
"""
import logging
from PyQt4 import QtCore, QtWebKit, QtNetwork
from mellowplayer.settings import Settings


def _logger():
    return logging.getLogger(__name__)


class CookieJar(QtNetwork.QNetworkCookieJar):
    def __init__(self):
        super(CookieJar, self).__init__()
        _logger().debug('loading cookies')
        val = Settings().cookies
        if val:
            val = eval(val)
            self.setAllCookies(QtNetwork.QNetworkCookie.parseCookies('\n'.join(val.values())))
        _logger().info('%d cookies loaded', len(self.allCookies()))

    def setCookiesFromUrl(self, cookie_list, url):
        val = Settings().cookies
        if val is None:
            val = {}
        else:
            val = eval(val)
        for cookie in cookie_list:
            val[str(cookie.name())] = bytes(cookie.toRawForm()).decode()
        Settings().cookies = repr(val)
        return super(CookieJar, self).setCookiesFromUrl(cookie_list, url)


class WebView(QtWebKit.QWebView):
    def __init__(self, parent=None):
        super(WebView, self).__init__(parent)
        self.cookieJar = CookieJar()
        self.page().networkAccessManager().setCookieJar(self.cookieJar)
        settings = self.settings()
        settings.setAttribute(QtWebKit.QWebSettings.PluginsEnabled, True)
