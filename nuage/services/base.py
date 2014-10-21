"""
This module contains the base class that represents a cloud music service
"""
from PyQt4 import QtCore


class MusicService(QtCore.QObject):
    """
    Base abstract class that represents a cloud music service.

    Defines the expected interface and provides utility methods for running
    some javascript on the main page.
    """
    #: Service URL
    url = None

    def __init__(self):
        #: reference to the main web view
        self._web_view = None

    def play(self):
        """
        Plays the current song.
        """
        raise NotImplementedError()

    def pause(self):
        """
        Pauses the current song
        """
        raise NotImplementedError()

    def stop(self):
        """
        Stops the current song
        """
        raise NotImplementedError()

    def get_song_status(self):
        """
        Get song status (playing, paused, stop or None)

        :return: status string
        """
        return None

    def get_song_infos(self):
        """
        Gets song information (dict).
        """
        return None

    def jseval(self, script):
        """
        Evalutes the ``script`` on the main page

        :param script: Script to execute (must written in Javascript).

        :return: The results of the evaluation.
        """
        return self._web_view.page().mainFrame().evaluateJavaScript(script)
