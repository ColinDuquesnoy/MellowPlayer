import logging
import os
import sys
from PyQt4 import QtGui
from mellowplayer import __version__, logger
from mellowplayer.gui.main_window import MainWindow


def main():
    logger.setup(verbose=False)
    app = QtGui.QApplication(sys.argv)
    window = MainWindow()
    window.show()
    window.services.start('Grooveshark')
    app.exec_()


if __name__ == '__main__':
    main()
