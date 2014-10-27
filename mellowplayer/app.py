import logging
import sys
from PyQt4 import QtCore, QtGui
from mellowplayer import __version__, logger
from mellowplayer.gui.main_window import MainWindow


def _logger():
    return logging.getLogger(__name__)


class Application(QtGui.QApplication):
    def __init__(self):
        QtGui.QApplication.setAttribute(
            QtCore.Qt.AA_CaptureMultimediaKeys, True)
        super().__init__(sys.argv)
        self.window = MainWindow()

    def run(self):
        self.window.showMaximized()
        # self.window.hide()
        self.exec_()
        del self.window


def main():
    logger.setup(verbose=False)
    Application().run()


if __name__ == '__main__':
    main()
