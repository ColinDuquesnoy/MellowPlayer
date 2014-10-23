import logging
import sys
from PyQt5 import QtWidgets
from mellowplayer import __version__, logger
from mellowplayer.gui.main_window import MainWindow


def main():
    logger.setup(verbose=False)
    app = QtWidgets.QApplication(sys.argv)
    window = MainWindow()
    window.show()
    window.services.start('Grooveshark')
    app.exec_()


if __name__ == '__main__':
    main()
