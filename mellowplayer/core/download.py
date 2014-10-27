"""
Contains the file downloader helper class
"""
import logging
from PyQt4 import QtCore, QtNetwork
import time


def _logger():
    return logging.getLogger(__name__)


class FileDownloader(QtCore.QObject):
    finished = QtCore.pyqtSignal(str)

    def __init__(self, url, dest_path):
        super().__init__()
        self._url = url
        self._dest = dest_path
        self._nam = QtNetwork.QNetworkAccessManager()
        self._nam.finished.connect(self._on_download_finished)

    def start(self):
        self._start = time.time()
        self._nam.get(QtNetwork.QNetworkRequest(self._url))
        _logger().info('downloading %s from %s', self._dest, str(self._url))

    def _on_download_finished(self, reply):
        _logger().info('download finished in %f [s]',
                       (time.time() - self._start))
        with open(self._dest, 'wb') as f:
            f.write(reply.readAll())
        self.finished.emit(self._dest)
