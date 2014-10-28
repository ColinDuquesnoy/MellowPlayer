import logging
from PyQt4 import QtCore, QtDBus
from mellowplayer.api import SongStatus, Song


def _logger():
    return logging.getLogger(__name__)


class MPRIS2Helper(object):
    def __init__(self):
        self.signal = QtDBus.QDBusMessage.createSignal(
            "/org/mpris/MediaPlayer2",
            "org.freedesktop.DBus.Properties",
            "PropertiesChanged"
        )

    def PropertiesChanged(self, interface, name, values):
        """Sends PropertiesChanged signal through sessionBus.

        Args:
            interface: interface name
            property: property name
            values: actual property value(s)

        """
        self.signal.setArguments(
            [interface, {name: values},
             QtCore.QVariant(QtCore.QVariant.StringList)]
        )
        _logger().info('sending PropertiesChanged signal for %s, %s, %s',
                        interface, name, values)
        if not QtDBus.QDBusConnection.sessionBus().send(self.signal):
            _logger().warning('failed to send PropertiesChanged signal for '
                              '%s, %s, %s', interface, name, values)


SERVICE_NAME = 'org.mpris.MediaPlayer2.mellowplayer'
OBJECT_NAME = '/org/mpris/MediaPlayer2'


class Mpris2(QtCore.QObject):
    def __init__(self, main_window):
        super().__init__()
        self.main_window = main_window
        self.root_adaptor = MPRISRoot(self)
        self.player_adaptor = MPRISPlayer(self)
        if not QtDBus.QDBusConnection.sessionBus().registerService(
                SERVICE_NAME):
            _logger().warning('Failed to register service %s on the session '
                              'bus' % SERVICE_NAME)
            return
        if not QtDBus.QDBusConnection.sessionBus().registerObject(
                OBJECT_NAME, self):
            _logger().warning('Failed to register object %s on the session '
                              'bus' % OBJECT_NAME)
            return
        _logger().info('MPRIS2 service started')

    def destroy(self):
        _logger().info('MPRIS2 service destroyed')
        QtDBus.QDBusConnection.sessionBus().unregisterObject(
            OBJECT_NAME)


class MPRISPlayer(QtDBus.QDBusAbstractAdaptor):
    QtCore.Q_CLASSINFO("D-Bus Interface", "org.mpris.MediaPlayer2.Player")

    def __init__(self, parent):
        super().__init__(parent)
        self.setAutoRelaySignals(True)
        self.player = self.parent().main_window.player
        self._helper = MPRIS2Helper()
        self.player.playback_status_changed.connect(
            self._on_playback_status_changed)
        self.player.song_changed.connect(self._on_song_changed)
        self.player.art_ready.connect(self._on_art_ready)

    def _on_art_ready(self):
        self._emit_metadata(self._current_song)

    def _on_playback_status_changed(self):
        _logger().debug('playback status changed: %s', self.PlaybackStatus)
        self._helper.PropertiesChanged(
            'org.mpris.MediaPlayer2.Player', 'PlaybackStatus',
            self.PlaybackStatus)

    def _on_song_changed(self, song):
        _logger().info('song changed: %r' % song)
        self._emit_metadata(song)

    @property
    def _current_song(self):
        return self.player.get_current_song()

    @QtCore.pyqtProperty(str)
    def PlaybackStatus(self):
        status = 'Stopped'
        if self._current_song:
            status = SongStatus.to_string(self._current_song.status)
            if status == 'Loading':
                status = 'Playing'
        return status

    @QtCore.pyqtProperty(str)
    def LoopStatus(self):
        """Returns current loop status.

        Should be 'None', 'Track' or 'Playlist', but returns 'None'
        for now, because there's no loop support in the player.

        """
        return "None"  # that's temporary

    @LoopStatus.setter
    def LoopStatus(self, loops):
        """Sets looping type.

        Does nothing for now as there's no loop support in the player.

        """
        pass

    @QtCore.pyqtProperty(float)
    def Rate(self):
        return 1.0

    @Rate.setter
    def Rate(self, value):
        pass

    @QtCore.pyqtProperty(bool)
    def Shuffle(self):
        return False

    @Shuffle.setter
    def Shuffle(self, value):
        pass

    @QtCore.pyqtProperty('QMap<QString, QVariant>')
    def Metadata(self):
        return self.to_xesam(self._current_song)

    def to_xesam(self, song):
        try:
            from PyQt4.QtDBus import QDBusObjectPath
        except ImportError:
            metadata = {}
        else:
            if song:
                artist = QtCore.QVariant([song.artist])
                artist.convert(QtCore.QVariant.StringList)
                metadata = {
                    'mpris:trackid': QDBusObjectPath(
                        '/org/mpris/MediaPlayer2/Track/%d' % id(song.name)),
                    'xesam:title': song.name,
                    'xesam:album': song.album,
                    'xesam:artist': artist,
                }
                if self.player.art:
                    metadata['mpris:artUrl'] = self.player.art
            else:
                metadata = {
                    'mpris:trackid': QDBusObjectPath(
                        '/org/mpris/MediaPlayer2/NoTrack'),
                    'xesam:title': '',
                    'xesam:album': '',
                    'xesam:albumArtist': '',
                    'xesam:artist': '',
                }
        return metadata

    def _emit_metadata(self, song):
        self._helper.PropertiesChanged(
            "org.mpris.MediaPlayer2.Player", "Metadata",
            self.to_xesam(self._current_song)
        )

    @QtCore.pyqtProperty(float)
    def Volume(self):
        return 1.0

    @QtCore.pyqtProperty(int)
    def Position(self):
        if self._current_song:
            # convert seconds to micro seconds
            return self._current_song.position.total_seconds() * 1000000
        else:
            return 0

    @QtCore.pyqtProperty(float)
    def MinimumRate(self):
        return 1.0

    @QtCore.pyqtProperty(float)
    def MaximumRate(self):
        return 1.0

    @QtCore.pyqtProperty(bool)
    def CanGoNext(self):
        return True

    @QtCore.pyqtProperty(bool)
    def CanGoPrevious(self):
        return True

    @QtCore.pyqtProperty(bool)
    def CanPlay(self):
        return True

    @QtCore.pyqtProperty(bool)
    def CanPause(self):
        return True

    @QtCore.pyqtProperty(bool)
    def CanSeek(self):
        return False

    @QtCore.pyqtProperty(bool)
    def CanControl(self):
        return True

    @QtCore.pyqtSlot()
    def Next(self):
        self.player.next()

    @QtCore.pyqtSlot()
    def Previous(self):
        self.player.previous()

    @QtCore.pyqtSlot()
    def PlayPause(self):
        self.player.play_pause()

    @QtCore.pyqtSlot()
    def Play(self):
        self.player.play_pause()

    @QtCore.pyqtSlot()
    def Pause(self):
        self.player.play_pause()

    @QtCore.pyqtSlot()
    def Stop(self):
        self.player.stop()

    @QtCore.pyqtSlot(float)
    def Seek(self, val):
        pass

    @QtCore.pyqtSlot()
    def SetPosition(self, track_id, pos):
        pass

    @QtCore.pyqtSlot(str)
    def OpenUri(self, uri):
        pass


class MPRISRoot(QtDBus.QDBusAbstractAdaptor):
    """ This provides the DBus adaptor to the outside world"""
    QtCore.Q_CLASSINFO("D-Bus Interface", 'org.mpris.MediaPlayer2')

    # org.mpris.MediaPlayer2 MPRIS 2.0 Root interface
    @QtCore.pyqtProperty(bool)
    def CanRaise(self):
        return True

    @QtCore.pyqtProperty(bool)
    def CanQuit(self):
        return True

    @QtCore.pyqtProperty(bool)
    def HasTrackList(self):
        return False

    @QtCore.pyqtProperty(str)
    def Identity(self):
        return 'Mellow Player'

    @QtCore.pyqtProperty(str)
    def DesktopEntry(self):
        return 'mellowplayer'

    @QtCore.pyqtProperty(list)
    def SupportedUriSchemes(self):
        return ['http', 'file']

    @QtCore.pyqtProperty(list)
    def SupportedMimeTypes(self):
        return []

    # // org.mpris.MediaPlayer2 MPRIS 2.2 Root interface
    @QtCore.pyqtProperty(bool)
    def CanSetFullscreen(self):
        return True

    @QtCore.pyqtProperty(bool)
    def Fullscreen(self):
        return False

    @Fullscreen.setter
    def Fullscreen(self, value):
        pass

    @QtCore.pyqtSlot()
    def Raise(self):
        self.parent().main_window.show()
        self.parent().main_window.raise_()

    @QtCore.pyqtSlot()
    def Quit(self):
        self.parent().main_window.quit()
