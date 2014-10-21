import logging
import sys
from PyQt4 import QtGui
from mellowplayer import __version__, logger
from mellowplayer.gui.main_window import MainWindow


def main():
    logger.setup(verbose=False)
    # logger.setup(verbose=True)
    logging.getLogger(__name__).info('MellowPlayer %s', __version__)
    app = QtGui.QApplication(sys.argv)
    window = MainWindow()
    window.show()
    window.services.start('Grooveshark')
    app.exec_()
