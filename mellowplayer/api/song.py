import datetime
import json


class SongStatus:
    Loading = 0
    Playing = 1
    Paused = 2
    Stopped = 3

    @classmethod
    def to_string(cls, val):
        return {
            cls.Loading: '[Loading]',
            cls.Playing: '[Playing]',
            cls.Paused: '[Paused]',
            cls.Stopped: '[Stopped]'
        }[val]


class Song:
    def __init__(self):
        self.song_id = None
        self.artist = ''
        self.art_url = ''
        self.album = ''
        self.name = ''
        self.duration = datetime.timedelta(seconds=0)
        self.position = datetime.timedelta(seconds=0)
        self.status = SongStatus.Loading

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
