"""
This module contains the Grooveshark service implementation.
"""
from mellowplayer.api import ServiceIntegration


class GroovesharkServiceIntegration(ServiceIntegration):
    """
    Official service that provides Grooveshark integration using the
    `Grooveshark JavaScript API`_

    .. _Grooveshark JavaScript API:
        http://developers.grooveshark.com/docs/js_api/

    """
    def play(self):
        self.jseval('window.Grooveshark.play();')

    def pause(self):
        self.jseval('window.Grooveshark.pause();')

    def stop(self):
        self.jseval('window.Grooveshark.stop();')

    def next(self):
        self.jseval('window.Grooveshark.next();')

    def previous(self):
        self.jseval('window.Grooveshark.previous();')

    def _get_current_song(self):
        return self.jseval(
            'current_song = window.Grooveshark.getCurrentSongStatus()')

    def get_song_status(self):
        try:
            return self._get_current_song()['status']
        except TypeError:
            return None

    def get_song_infos(self):
        try:
            return self._get_current_song()['song']
        except TypeError:
            return None
