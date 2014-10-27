import datetime
import json
from PyQt4 import QtDBus


class SongStatus:
    Loading = 0
    Playing = 1
    Paused = 2
    Stopped = 3

    @classmethod
    def to_string(cls, val):
        return {
            cls.Loading: 'Loading',
            cls.Playing: 'Playing',
            cls.Paused: 'Paused',
            cls.Stopped: 'Stopped'
        }[val]


class Song:
    @property
    def song_id(self):
        return self._song_id

    @song_id.setter
    def song_id(self, value):
        self._song_id = value

    @property
    def artist(self):
        return self._artist

    @artist.setter
    def artist(self, value):
        self._artist = str(value)

    @property
    def art_url(self):
        return self._art_url

    @art_url.setter
    def art_url(self, value):
        self._art_url = str(value)

    @property
    def album(self):
        return self._album

    @album.setter
    def album(self, value):
        self._album = str(value)

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, value):
        self._name = str(value)

    def __init__(self):
        self._song_id = None
        self._artist = ''
        self._art_url = ''
        self._album = ''
        self._name = ''
        self.duration = datetime.timedelta(seconds=0)
        self.position = datetime.timedelta(seconds=0)
        self._status = SongStatus.Loading

    @property
    def data(self):
        """
        Gets/Sets the song data dict (useful for serialization)
        """
        return {
            'name': self.name,
            'artist': self.artist,
            'album': self.album,
            'position': self.position.total_seconds(),
            'duration': self.duration.total_seconds(),
            'status': self.status
        }

    @data.setter
    def data(self, value):
        self.name = value['name']
        self.artist = value['artist']
        self.album = value['album']
        self.position = datetime.timedelta(seconds=value['position']),
        self.duration = datetime.timedelta(seconds=value['duration']),
        self.status = value['status']

    def __eq__(self, other):
        if other:
            return self.song_id == other.song_id
        return False

    def __str__(self):
        return '%s by %s on %s' % (self.name, self.artist, self.album)

    def pretty_string(self):
        return '<b>%s</b> by <b>%s</b> on <b>%s</b>' % (
            self.name, self.artist, self.album)

    def __repr__(self):
        return repr(self.data)

    @classmethod
    def to_xesam(cls, song):
        if song:
            metadata = {
                'mpris:trackid': QtDBus.QDBusObjectPath(
                    '/org/mpris/MediaPlayer2/Track%d' % id(song.name)),
                'xesam:title': song.name,
                'xesam:artUrl': song.art_url,
                'xesam:album': song.album,
                'xesam:albumArtist': song.artist,
                'xesam:artist': song.artist,
            }
        else:
            metadata = {
                'mpris:trackid': QtDBus.QDBusObjectPath(
                    '/org/mpris/MediaPlayer2/NoTrack'),
                'xesam:title': '',
                'xesam:url': '',
                'xesam:album': '',
                'xesam:albumArtist': '',
                'xesam:artist': '',
            }
        return metadata
