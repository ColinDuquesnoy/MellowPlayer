"""
This module contains the webview and the cookie jar used by the main window.
"""
import logging
from PyQt4 import QtCore, QtWebKit, QtNetwork


def _logger():
    return logging.getLogger(__name__)


class CookieJar(QtNetwork.QNetworkCookieJar):
    def __init__(self, cookies_key, parent=None):
        super(CookieJar, self).__init__(parent)
        _logger().debug('loading cookies')
        self.main_window = parent
        # self.main_window.settings.clear()
        self._key = cookies_key
        val = self.main_window.settings.value(self._key)
        if val:
            val = eval(val)
            self.setAllCookies(QtNetwork.QNetworkCookie.parseCookies('\n'.join(val.values())))
        _logger().info('%d cookies loaded', len(self.allCookies()))

    def setCookiesFromUrl(self, cookie_list, url):
        val = self.main_window.settings.value(self._key)
        if val is None:
            val = {}
        else:
            val = eval(val)
        for cookie in cookie_list:
            val[str(cookie.name())] = bytes(cookie.toRawForm()).decode()
        self.main_window.settings.setValue(self._key, repr(val))
        return super(CookieJar, self).setCookiesFromUrl(cookie_list, url)


class WebView(QtWebKit.QWebView):
    def __init__(self, cookies_key, parent=None):
        super(WebView, self).__init__(parent)
        self.cookieJar = CookieJar(cookies_key, parent)
        self.page().networkAccessManager().setCookieJar(self.cookieJar)
        settings = self.settings()
        settings.setAttribute(QtWebKit.QWebSettings.PluginsEnabled, True)
