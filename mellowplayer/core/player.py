"""
This module contains the player object that drives the cloud service player
throught an integration plugin
"""
import os
import tempfile
from PyQt4 import QtCore
from mellowplayer.api import SongStatus
from .download import FileDownloader


class Player(QtCore.QObject):
    song_changed = QtCore.pyqtSignal(object)
    playback_status_changed = QtCore.pyqtSignal(str)
    art_ready = QtCore.pyqtSignal(str)

    def __init__(self):
        QtCore.QObject.__init__(self)
        self.service = None
        self._prev_status = SongStatus.Stopped
        self._prev_song = None

    def toggle(self):
        if not self.service:
            return
        if self.current_song.status > SongStatus.Playing:
            self.service.integration.play()
        else:
            self.service.integration.pause()

    def play(self):
        if self.service:
            self.toggle()

    def stop(self):
        if self.service:
            self.service.integration.stop()

    def pause(self):
        if self.service:
            self.toggle()

    def next(self):
        if self.service:
            self.service.integration.next()

    def previous(self):
        if self.service:
            self.service.integration.previous()

    def _check_for_status_changes(self, song):
        if song:
            status = song.status
        else:
            status = SongStatus.Stopped
        if status != self._prev_status:
            self.playback_status_changed.emit(SongStatus.to_string(status))
            self._prev_status = status

    def _download_art(self):
        song = self.get_current_song()
        url = song.art_url
        tmp_dir = os.path.join(
            tempfile.gettempdir(), 'mellowplayer', 'album-arts')
        ext = os.path.splitext(url)[1]
        try:
            os.makedirs(tmp_dir)
        except OSError:
            # dir already created
            pass
        artist = song.artist.replace(' ', '')
        album = song.album.replace(' ', '')
        name = '%s-%s' % (artist, album)
        save_path = os.path.join(tmp_dir, name + ext)
        if os.path.exists(save_path):
            self.art_ready.emit(save_path)
        else:
            self.downloader = FileDownloader(QtCore.QUrl(url), save_path)
            self.downloader.finished.connect(self.art_ready.emit)
            self.downloader.start()

    def _check_for_song_changes(self, song):
        if song != self._prev_song:
            self._prev_song = song
            self.song_changed.emit(song)
            if song:
                self._download_art()

    def get_current_song(self):
        if self.service:
            song = self.service.integration.current_song()
            return song
        return None

    def update(self):
        song = self.service.integration.current_song()
        self._check_for_song_changes(song)
        self._check_for_status_changes(song)
        return song
