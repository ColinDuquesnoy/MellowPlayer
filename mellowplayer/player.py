"""
This module contains the player object that drives the cloud service player
throught an integration plugin
"""
import os
import tempfile

from .api import SongStatus
from .utils import FileDownloader
from .qt import QtCore


class Player(QtCore.QObject):
    """
    Helps manipulating the service integration plugin to interact with
    the service: play, pause, get song infos,...
    """
    #: Signal emitted when a song changed
    song_changed = QtCore.pyqtSignal(object)
    #: Signal emitted when the playback status changed
    playback_status_changed = QtCore.pyqtSignal(str)
    #: Signal emitted when the art for the current song is ready.
    art_ready = QtCore.pyqtSignal()

    def __init__(self):
        QtCore.QObject.__init__(self)
        #: Integration service plugin
        self.service = None
        self._prev_status = SongStatus.Stopped
        self._prev_song = None
        #: art file path, use it when art_ready has been emitted.
        self.art = ''

    def play_pause(self):
        """
        Plays or pauses the current song depending on its playback status.
        """
        if not self.service or not self.get_current_song():
            return
        if self.get_current_song().status > SongStatus.Playing:
            self.service.play()
        else:
            self.service.pause()

    def stop(self):
        """
        Stops the current song.
        """
        if self.service:
            self.service.stop()

    def next(self):
        """
        Goes to the next song
        """
        if self.service:
            self.service.next()

    def previous(self):
        """
        Goes to the previous song.
        """
        if self.service:
            self.service.previous()

    def get_current_song(self):
        """
        Gets the current song info

        :return: current song or None
        """
        if self.service:
            song = self.service.current_song()
            return song
        return None

    def update(self):
        """
        Update player status and emit status change signals if
        a change occured.

        This method should be called periodically to ensure correct player
        states.
        """
        if self.service:
            song = self.service.current_song()
            self._check_for_song_changes(song)
            self._check_for_status_changes(song)
            return song
        return None

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

        tmp_dir = tempfile.gettempdir()
        ext = os.path.splitext(url)[1]
        artist = song.artist.replace(
            ' ', '').replace('\\', '').replace('/', '')
        album = song.album.replace(
            ' ', '').replace('\\', '').replace('/', '')
        name = '%s-%s' % (artist, album)
        save_path = os.path.join(tmp_dir, name + ext)
        if os.path.exists(save_path):
            self._on_art_ready(save_path)
        else:
            self.downloader = FileDownloader(QtCore.QUrl(url), save_path)
            self.downloader.finished.connect(self._on_art_ready)
            self.downloader.start()

    def _on_art_ready(self, art):
        self.art = 'file://%s' % art
        self.art_ready.emit()

    def _check_for_song_changes(self, song):
        if song != self._prev_song:
            self._art = ''
            self._prev_song = song
            self.song_changed.emit(song)
            if song:
                self._download_art()
