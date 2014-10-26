from PyQt4 import QtCore, QtGui
from mellowplayer import __version__
from mellowplayer.api import ServiceManager
from .dlg_select_service import DlgSelectService
from .forms.main_window_ui import Ui_MainWindow
from mellowplayer.settings import Settings


class MainWindow(QtGui.QMainWindow):
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
        self._init_tray_icon()

    #--- system tray icon and close logic
    def close(self):
        self.hide()
        super().close()

    def closeEvent(self, ev=None):
        hide = ev is not None and self.isVisible()
        if hide:
            if not Settings().flg_close:
                QtGui.QMessageBox.information(
                    self, 'Mellow Player',
                    'The program will keep running in the '
                    'system tray. To terminate the program, '
                    'choose <b>Quit</b> in the context menu '
                    'of the system tray entry.')
                Settings().flg_close = True
            self.hide()
            ev.ignore()

    def _init_tray_icon(self):
        self.tray_icon = QtGui.QSystemTrayIcon(self)
        self.tray_icon.setIcon(self.windowIcon())
        menu = QtGui.QMenu(self)
        action_restore = QtGui.QAction('Restore window', self)
        action_restore.triggered.connect(self.show)
        action_restore.setIcon(QtGui.QIcon.fromTheme(
            'Restore', QtGui.QIcon(':/view-restore.svg')))
        menu.addAction(action_restore)
        menu.addSeparator()
        menu.addActions(self.ui.menuPlayback.actions())
        menu.addSeparator()
        menu.addActions(self.ui.menuApplication.actions())
        self.tray_icon.setContextMenu(menu)
        self.tray_icon.show()
        self.tray_icon.activated.connect(self._on_tray_icon_activated)

    def _on_tray_icon_activated(self, reason):
        if reason in (QtGui.QSystemTrayIcon.Trigger,
                      QtGui.QSystemTrayIcon.DoubleClick):
            self.show()

    def setVisible(self, visible):
        super().setVisible(visible)
        if Settings().always_show_tray_icon:
            self.tray_icon.show()
        else:
            # only show tray if the window is not visible
            self.tray_icon.setVisible(not visible)

    #--- slots
    @QtCore.pyqtSlot()
    def on_pushButtonSelect_clicked(self):
        self._select_service()

    @QtCore.pyqtSlot()
    def on_actionSelect_service_triggered(self):
        self._select_service()

    @QtCore.pyqtSlot()
    def on_actionReport_a_bug_triggered(self):
        QtGui.QDesktopServices.openUrl(QtCore.QUrl.fromEncoded(
            'https://github.com/ColinDuquesnoy/MellowPlayer/issues/new?tit'
            'le=Issue%3A &body=%23%23%23%20Description%20of%20the%20issue%0A%'
            '0A%0A%23%23%23%20System%20information%0A*%20Operating%20System%3A'
            '%20%0A*%20Mellow%20Player%20Version%3A%0A*%20Service%3A%0A*%20'
            'Service%20version'))

    @QtCore.pyqtSlot()
    def on_actionPlay_triggered(self):
        self.services.play()

    @QtCore.pyqtSlot()
    def on_actionPause_triggered(self):
        self.services.pause()

    @QtCore.pyqtSlot()
    def on_actionStop_triggered(self):
        self.services.stop()

    @QtCore.pyqtSlot()
    def on_actionNext_triggered(self):
        self.services.next()

    @QtCore.pyqtSlot()
    def on_actionPrevious_triggered(self):
        self.services.previous()

    #--- internal helper methods
    def _start_current(self):
        if self.services.start_current_service():
            self.ui.stackedWidget.setCurrentIndex(1)
        else:
            self.ui.stackedWidget.setCurrentIndex(0)

    def _select_service(self):
        self.show()
        service = DlgSelectService.select_service(self)
        if service and service != self.services.current_service:
            self.services.current_service = service
            self._start_current()
