import logging

from mellowplayer.api import SongStatus
from mellowplayer.qt import QtCore, QtGui, QtWidgets, QT_API
from mellowplayer.settings import Settings
from .dlg_select_service import DlgSelectService
from .forms.main_window_ui import Ui_MainWindow


def _logger():
    return logging.getLogger(__name__)


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self, app):
        super(MainWindow, self).__init__()
        self.app = app
        self._setup_ui()
        self._init_tray_icon()
        self.ui.webView.page().linkClicked.connect(self._on_link_clicked)

    def _setup_ui(self):
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)
        self._setup_icons()
        self.ui.pushButtonQuit.clicked.connect(self.quit)
        self.ui.actionQuit.triggered.connect(self.quit)
        self.ui.pushButtonSelect.setFocus()
        # configure update timer
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect(self._on_timeout)
        self.timer.start(10)

    def _setup_icons(self):
        def _icon(theme, path):
            return QtGui.QIcon.fromTheme(theme, QtGui.QIcon(path))

        self.ic_app = QtGui.QIcon(':/application-x-mellowplayer.png')
        self.ic_preferences = _icon(
            'preferences-system', ':/preferences-system.svg')
        self.ic_play = _icon(
            'media-playback-start', ':/media-playback-start.svg')
        self.ic_pause = _icon(
            'media-playback-pause', ':/media-playback-pause.svg')
        self.ic_stop = _icon(
            'media-playback-stop', ':/media-playback-stop.svg')
        self.ic_next = _icon('media-seek-forward', ':/media-seek-forward.svg')
        self.ic_previous = _icon(
            'media-seek-backward', ':/media-seek-backward.svg')
        self.ic_help_about = _icon('help-about', ':/help-about.svg')
        self.ic_report_bug = _icon(
            'tools-report-bug', ':/tools-report-bug.svg')
        self.ic_quit = _icon(
            'application-exit', ':/application-exit.svg')
        self.ic_restore = _icon(
            'view-restore', ':/view-restore.svg')

        self.ui.actionPlayPause.setIcon(self.ic_play)
        self.ui.actionStop.setIcon(self.ic_stop)
        self.ui.actionNext.setIcon(self.ic_next)
        self.ui.actionPrevious.setIcon(self.ic_previous)
        self.ui.actionAbout_MellowPlayer.setIcon(self.ic_help_about)
        self.ui.actionPreferences.setIcon(self.ic_preferences)
        self.ui.actionReport_a_bug.setIcon(self.ic_report_bug)
        self.ui.actionQuit.setIcon(self.ic_quit)
        self.ui.actionSelect_service.setIcon(self.ic_app)
        self.ui.pushButtonSelect.setIcon(self.ic_app)
        self.ui.pushButtonPreferences.setIcon(self.ic_preferences)
        self.ui.pushButtonQuit.setIcon(self.ic_quit)

    #--- Update song status and infos
    def _on_timeout(self):
        """
        Get current song and update gui accordingly.
        """
        if not self.app:
            return
        song = self.app.player.update()
        if song:
            self.setWindowTitle(
                '%s - MellowPlayer' % str(song))
            self.tray_icon.setToolTip(
                '%s - MellowPlayer' % song.pretty_string())
            self.ui.actionNext.setEnabled(True)
            self.ui.actionPrevious.setEnabled(True)
            self.ui.actionStop.setEnabled(song.status != SongStatus.Stopped)
            self.ui.actionPlayPause.setEnabled(True)
            self.ui.actionPlayPause.setText(str(song))
            if song.status == SongStatus.Paused:
                self.ui.actionPlayPause.setIcon(self.ic_play)
            else:
                self.ui.actionPlayPause.setIcon(self.ic_pause)
        else:
            self.setWindowTitle('MellowPlayer')
            self.tray_icon.setToolTip('MellowPlayer')
            self.ui.actionNext.setEnabled(False)
            self.ui.actionPrevious.setEnabled(False)
            self.ui.actionStop.setEnabled(False)
            self.ui.actionPlayPause.setEnabled(False)
            self.ui.actionPlayPause.setText('Play/Pause')
            self.ui.actionPlayPause.setIcon(self.ic_play)

    #--- system tray icon and close logic
    def quit(self):
        self._quit = True
        self.app.player.stop()
        self.close()

    def closeEvent(self, ev=None):
        visible = ev is not None and self.isVisible()
        if self.app:
            song = self.app.player.get_current_song()
            # exit on close if not playing
            visible &= ((song is not None and song.status <= SongStatus.Playing)
                        or not Settings().exit_on_close_if_not_playing)
        else:
            visible = False
        if visible and not hasattr(self, '_quit'):
            if not Settings().flg_close:
                QtWidgets.QMessageBox.information(
                    self, 'Mellow Player',
                    'The program will keep running in the '
                    'system tray. To terminate the program, '
                    'choose <b>Quit</b> in the context menu '
                    'of the system tray entry.')
                Settings().flg_close = True
            self.hide()
            ev.ignore()
        else:
            super().closeEvent(ev)
            self.timer.stop()
            self.tray_icon.hide()

    def _init_tray_icon(self):
        self.tray_icon = QtWidgets.QSystemTrayIcon(self)
        self.tray_icon.setIcon(QtGui.QIcon(Settings().tray_icon))
        if QT_API == 4:
            # cause a segfault on exit with PyQt5 (Qt 5.4)
            menu = QtWidgets.QMenu(self)
            action_restore = QtWidgets.QAction('Restore window', self)
            action_restore.triggered.connect(self.show)
            action_restore.setIcon(self.ic_restore)
            menu.addAction(action_restore)
            self.action_restore = action_restore
            menu.addSeparator()
            menu.addActions(self.ui.menuPlayback.actions())
            menu.addSeparator()
            menu.addActions(self.ui.menuApplication.actions())
            self.tray_icon.setContextMenu(menu)
        self.tray_icon.show()
        self.tray_icon.activated.connect(self._on_tray_icon_activated)

    def _on_tray_icon_activated(self, reason):
        if reason in (QtWidgets.QSystemTrayIcon.Trigger,
                      QtWidgets.QSystemTrayIcon.DoubleClick):
            self.show()

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
    def on_actionPlayPause_triggered(self):
        self.app.player.play_pause()

    @QtCore.pyqtSlot()
    def on_actionStop_triggered(self):
        self.app.player.stop()

    @QtCore.pyqtSlot()
    def on_actionNext_triggered(self):
        self.app.player.next()

    @QtCore.pyqtSlot()
    def on_actionPrevious_triggered(self):
        self.app.player.previous()

    @QtCore.pyqtSlot(QtCore.QUrl)
    def _on_link_clicked(self, url):
        """
        Allow the user to open external links (such as wikipedia pages).

        :param url: url of the clicked link
        """
        if self.app.services.current_service.url in url.toString():
            self.ui.webView.load(url)
        else:
            QtGui.QDesktopServices.openUrl(url)

    #--- internal helper methods
    def show_page(self, home=False):
        if home:
            self.ui.stackedWidget.setCurrentIndex(0)
            self.ui.menubar.hide()
        else:
            self.ui.stackedWidget.setCurrentIndex(1)
            self.ui.menubar.show()

    def _select_service(self):
        self.show()
        service = DlgSelectService.select_service(self)
        if service and service != self.app.services.current_service_name:
            self.app.services.current_service_name = service
            self.app.start_current_service()
