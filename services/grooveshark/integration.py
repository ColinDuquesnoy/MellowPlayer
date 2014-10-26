"""
This module contains the Grooveshark service implementation.
"""
import datetime
from mellowplayer.api import ServiceIntegration, Song, SongStatus


class GroovesharkServiceIntegration(ServiceIntegration):
    """
    Official service that provides Grooveshark integration using the
    `Grooveshark JavaScript API`_

    .. _Grooveshark JavaScript API:
        http://developers.grooveshark.com/docs/js_api/

    """
    STATUS_MAP = {
        'loading': SongStatus.Loading,
        'playing': SongStatus.Playing,
        'paused': SongStatus.Paused,
        'stopped': SongStatus.Stopped
    }

    def play(self):
        self.jseval('window.Grooveshark.play();')

    def pause(self):
        self.jseval('window.Grooveshark.pause();')

    def stop(self):
        self.pause()

    def next(self):
        self.jseval('window.Grooveshark.next();')

    def previous(self):
        self.jseval('window.Grooveshark.previous();')

    def current_song(self):
        data = self.jseval(
            'current_song = window.Grooveshark.getCurrentSongStatus()')
        song = Song()
        try:
            song.song_id = data['song']['songID']
            song.name = data['song']['songName']
            try:
                song.status = self.STATUS_MAP[data['status']]
            except KeyError:
                song.status = SongStatus.Stopped
            song.album = data['song']['albumName']
            song.art_url = data['song']['artURL']
            song.artist = data['song']['artistName']
            song.album = data['song']['albumName']
            song.duration = datetime.timedelta(
                milliseconds=data['song']['calculatedDuration'])
            song.position = datetime.timedelta(
                milliseconds=data['song']['position'])
        except TypeError:
            return None
        return song
