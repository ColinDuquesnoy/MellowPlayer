from PyQt5 import QtCore, QtWidgets
from mellowplayer import __version__
from mellowplayer.api import ServiceManager
from .webview import WebView


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.settings = QtCore.QSettings("mellowplayer")
        self.web_view = WebView('cookies', parent=self)
        self.setCentralWidget(self.web_view)
        self.setWindowTitle('MellowPlayer %s' % __version__)
        self.services = ServiceManager(self.web_view)
