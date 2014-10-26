from PyQt4 import QtCore, QtGui
from mellowplayer import __version__
from mellowplayer.api import ServiceManager
from .dlg_select_service import DlgSelectService
from .forms.main_window_ui import Ui_MainWindow


class MainWindow(QtGui.QMainWindow):
    def _start_current(self):
        if self.services.start_current_service():
            self.ui.stackedWidget.setCurrentIndex(1)
        else:
            self.ui.stackedWidget.setCurrentIndex(0)

    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self.services = ServiceManager(self.ui.webView)
        self.setWindowTitle('MellowPlayer %s' % __version__)
        self.ui.pushButtonSelect.setFocus()
        self._start_current()
        self.ui.pushButtonQuit.clicked.connect(self.close)
        self.ui.actionQuit.triggered.connect(self.close)

    @QtCore.pyqtSlot()
    def on_pushButtonSelect_clicked(self):
        self._select_service()

    @QtCore.pyqtSlot()
    def on_actionSelect_service_triggered(self):
        self._select_service()

    def _select_service(self):
        service = DlgSelectService.select_service(self)
        if service and service != self.services.current_service:
            self.services.current_service = service
            self._start_current()

    @QtCore.pyqtSlot()
    def on_actionReport_a_bug_triggered(self):
        QtGui.QDesktopServices.openUrl(QtCore.QUrl.fromEncoded(
            'https://github.com/ColinDuquesnoy/MellowPlayer/issues/new?tit'
            'le=Issue%3A &body=%23%23%23%20Description%20of%20the%20issue%0A%'
            '0A%0A%23%23%23%20System%20information%0A*%20Operating%20System%3A'
            '%20%0A*%20Mellow%20Player%20Version%3A%0A*%20Service%3A%0A*%20'
            'Service%20version'))
