import logging
import sys
import weakref

from .qt import QtGui, QtWidgets, QtCore, QtNetwork
from .gui.main_window import MainWindow
from .player import Player
from .managers import PluginsManager, ServicesManager, ExtensionsManager


def _logger():
    return logging.getLogger(__name__)


class QSingleApplication(QtWidgets.QApplication):
    """
    This subclass of QApplication may be used to create a single instance only
    application. It uses a socket to detect if another application instance is
    already running.
    """

    def __init__(self, args, name="MellowPlayer"):
        QtWidgets.QApplication.__init__(self, args)
        self.name = name
        self.socket = QtNetwork.QLocalSocket()
        self.socket.connected.connect(self.on_socket_connected)
        self.socket.error.connect(self.on_socket_error)
        self.server = QtNetwork.QLocalServer()
        self.server.newConnection.connect(self.on_new_connection)
        self.main_window = None

    def single_start(self, main_window):
        """
        Starts the application. Connect the socket to the server and if the
        connection fails, create the server to prevent future instance from
        running.
        :return:
        """
        self.main_window = weakref.ref(main_window)
        self.socket.connectToServer(self.name, QtCore.QIODevice.WriteOnly)

    def on_socket_connected(self):
        """
        This mean the server is already running and thus we have to exit.
        :return:
        """
        _logger().warning("{0} is already running. The previous instance"
                          " will be shown instead.".format(self.name))
        QtCore.QTimer.singleShot(250.0, self.quit)

    def start_application(self):
        if not self.server.listen(self.name):
            _logger().warning("error listening the socket, single instance "
                              "won't work")
        self.main_window().show()

    def on_socket_error(self):
        """
        This means no server/application is running. We must start the local
        server and show the main window
        :return:
        """
        self.start_application()

    def on_new_connection(self):
        """
        This means another instance has been created and will leave soon. We
        must show the window
        :return:
        """
        print('Show main window')
        self.main_window().activateWindow()
        self.main_window().raise_()
        self.main_window().show()


class Application:
    def __init__(self):
        self.qapp = QSingleApplication(sys.argv)
        self.window = MainWindow(self)
        self.qapp.single_start(main_window=self.window)
        self.qapp.setWindowIcon(self.window.windowIcon())
        self.player = Player()
        self.plugin_manager = PluginsManager()
        self.services = ServicesManager(self.window.ui.webView, self.plugin_manager)
        self.extensions = ExtensionsManager(self.plugin_manager, self)
        self.start_current_service()

        # still very experimental.
        self._global_shortcuts = []
        try:
            # optional dependency
            from pygs import QxtGlobalShortcut
        except (ImportError, RuntimeError):
            _logger().warning('no global shortcut support, PyGlobalShortcuts '
                              'package not found')
        else:
            shortcut_pairs = [
                ('Play/Pause', ['Ctrl+Alt+P'], self.window.on_actionPlayPause_triggered),
                ('Stop', ['Ctrl+Alt+S'], self.window.on_actionStop_triggered),
                ('Next', ['Ctrl+Alt+F'], self.window.on_actionNext_triggered),
                ('Pevious', ['Ctrl+Alt+B'], self.window.on_actionPrevious_triggered),
            ]
            for name, shortcuts, slot in shortcut_pairs:
                for shortcut in shortcuts:
                    _logger().info('Registering global shortcut: %s -> %s', name, shortcut)
                    gs = QxtGlobalShortcut()
                    gs.setShortcut(QtGui.QKeySequence(shortcut))
                    gs.activated.connect(slot)
                    self._global_shortcuts.append(gs)

    def start_current_service(self):
        self.player.service = self.services.start_current_service()
        self.window.show_page(home=self.player.service is None)

    def run(self):
        self.window.show()
        self.qapp.exec_()
        self._global_shortcuts.clear()
        self.extensions.teardown()
        self.window.ui.webView.close()
        self.window.ui = None
        del self.window
        self.window = None
        del self.qapp
        self.qapp = None
