import sys
from nuage import __version__
from nuage.main_window import MainWindow
from PyQt4 import QtGui


def main():
    print('Nuage v%s' % __version__)
    app = QtGui.QApplication(sys.argv)
    window = MainWindow()
    window.show()
    window.start_service()
    app.exec_()

