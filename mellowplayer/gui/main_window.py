from PyQt4 import QtCore, QtGui
from mellowplayer import __version__
from mellowplayer.api import ServiceManager
from .web import WebView
from .forms.main_window_ui import Ui_MainWindow


class MainWindow(QtGui.QMainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.services = ServiceManager(self.ui.webView)
        self.setWindowTitle('MellowPlayer %s' % __version__)
        self.ui.pushButtonLoad.setFocus()
        self.ui.stackedWidget.setCurrentIndex(0)
