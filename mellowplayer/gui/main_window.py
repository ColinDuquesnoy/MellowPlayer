from PyQt5 import QtCore, QtWidgets
from mellowplayer import __version__
from mellowplayer.api import ServiceManager
from .web import WebView
from .forms.main_window_ui import Ui_MainWindow


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.services = ServiceManager(self.ui.webView)
        self.setWindowTitle('MellowPlayer %s' % __version__)
