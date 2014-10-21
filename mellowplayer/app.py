import sys
from PyQt4 import QtGui
from mellowplayer import __version__
from mellowplayer.gui.main_window import MainWindow


def main():
    print('MellowPlayer v%s' % __version__)
    app = QtGui.QApplication(sys.argv)
    window = MainWindow()
    window.show()
    window.services.start('Grooveshark')
    app.exec_()
