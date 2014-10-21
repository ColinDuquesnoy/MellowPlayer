from PyQt4 import QtCore, QtGui
from nuage.web import WebView
from nuage.services import AVAILABLE_SERVICES
from nuage import __version__


class MainWindow(QtGui.QMainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.settings = QtCore.QSettings("nuage")
        QtGui.QApplication.instance().setAttribute(
            QtCore.Qt.AA_CaptureMultimediaKeys, True)
        self.web_view = WebView('cookies', parent=self)
        self.setCentralWidget(self.web_view)
        self.setWindowTitle('Nuage v%s' % __version__)

    def start_service(self, service=AVAILABLE_SERVICES[0]()):
        self.service = service
        self.service._web_view = self.web_view
        self.web_view.load(QtCore.QUrl(service.url))
