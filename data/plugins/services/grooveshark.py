"""
This module contains the Grooveshark service implementation.
"""
import datetime
import os
from mellowplayer.api import Song, SongStatus, plugins


class GroovesharkServiceIntegration(plugins.IServiceIntegrationPlugin):
    """
    Official service that provides Grooveshark integration using the
    `Grooveshark JavaScript API`_

    .. _Grooveshark JavaScript API:
        http://developers.grooveshark.com/docs/js_api/

    """
    # Metadata
    url = 'http://grooveshark.com/'
    icon = os.path.join(os.path.dirname(__file__), 'grooveshark-logo.png')
    description = '''
    <p><strong>Grooveshark</strong> is an international online music search engine,
music streaming service and music recommendation web software application, allowing users
to search for, stream, and upload music that can be played immediately or added
to a playlist. An optional paid subscription adds additional functionality and removes
advertisements.
</p><p>
<em>Source:
<a href="http://en.wikipedia.org/wiki/Grooveshark">Grooveshark on Wikipedia</a>,
<a href="http://grooveshark.com">Official website</a></em>
</p>
'''

    # map MellowPlayer sound status to grooveshark's sound status
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
            sng = data['song']
            song.song_id = sng['songID']
            song.name = sng['songName']
            try:
                song.status = self.STATUS_MAP[data['status']]
            except KeyError:
                song.status = SongStatus.Stopped
            song.album = sng['albumName']
            song.art_url = sng['artURL']
            song.artist = sng['artistName']
            song.album = sng['albumName']
            song.duration = datetime.timedelta(
                milliseconds=sng['calculatedDuration'])
            song.position = datetime.timedelta(
                milliseconds=sng['position'])
        except TypeError:
            return None
        return song
