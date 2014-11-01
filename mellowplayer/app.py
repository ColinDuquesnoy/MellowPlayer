import logging
import sys
from mellowplayer import __version__, logger
from PyQt4 import QtCore, QtGui
from mellowplayer.gui.main_window import MainWindow


def _logger():
    return logging.getLogger(__name__)


class Application(QtGui.QApplication):
    def __init__(self):
        QtGui.QApplication.setAttribute(
            QtCore.Qt.AA_CaptureMultimediaKeys, True)
        super().__init__(sys.argv)
        self.window = MainWindow()

        self._global_shortcuts = []
        try:
            # optional dependency
            from pygs import QxtGlobalShortcut
        except ImportError:
            _logger().warning('no global shortcut support, PyGlobalShortcuts '
                              'package not found')
        else:
            shortcut_pairs = [
                (['Ctrl+Alt+P', 'Media Play'], self.window.on_actionPlayPause_triggered),
                (['Ctrl+Alt+S', 'Media Stop'], self.window.on_actionStop_triggered),
                (['Ctrl+Alt+F', 'Media Next'], self.window.on_actionNext_triggered),
                (['Ctrl+Alt+B', 'Media Previous'], self.window.on_actionPrevious_triggered),
            ]
            for shortcuts, slot in shortcut_pairs:
                for shortcut in shortcuts:
                    gs = QxtGlobalShortcut()
                    gs.setShortcut(QtGui.QKeySequence(shortcut))
                    gs.activated.connect(slot)
                    self._global_shortcuts.append(gs)

    def run(self):
        self.window.show()
        self.exec_()
        del self.window


def main():
    logger.setup(verbose=False)
    Application().run()


if __name__ == '__main__':
    main()
