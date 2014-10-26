import logging
from PyQt4 import QtCore, QtDBus


def _logger():
    return logging.getLogger(__name__)


class Mpris2(QtCore.QObject):
    path = '/org/mpris/MediaPlayer2'
    svname = 'org.mpris.MediaPlayer2.mellowplayer'
    freedesktop_path = 'org.freedesktop.DBus.Properties'

    # org.mpris.MediaPlayer2 MPRIS 2.0 Root interface
    @property
    def CanRaise(self):
        return True

    @property
    def CanQuit(self):
        return True

    @property
    def HasTrackList(self):
        return False

    @property
    def Identity(self):
        return 'MellowPlayer'

    @property
    def DesktopEntry(self):
        return 'mellowplayer.desktop'

    @property
    def SupportedUriSchemes(self):
        return ['http']

    @property
    def SupportedMimeTypes(self):
        return []

    # // org.mpris.MediaPlayer2 MPRIS 2.2 Root interface
    @property
    def CanSetFullscreen(self):
        return True

    @property
    def Fullscreen(self):
        return False

    @Fullscreen.setter
    def Fullscreen(self, value):
        pass

    # // org.mpris.MediaPlayer2.Player MPRIS 2.0 Player interface
    @property
    def PlaybackStatus(self):
        song = self.main_window.services.current_song
        if song:
            return song.status.to_string(song.status)
        return 'Stopped'

    @PlaybackStatus.setter
    def PlaybackStatus(self, value):
        if value == 'Paused':
            self.main_window.services.pause()
        elif value == 'Playing':
            self.main_window.services.play()
        elif value == 'Stooped':
            self.main_window.services.stop()

    @property
    def LoopStatus(self):
        return 'None'

    @LoopStatus.setter
    def LoopStatus(self, value):
        pass

    @property
    def Rate(self):
        return 1.0

    @Rate.setter
    def Rate(self, value):
        pass

    @property
    def Shuffle(self):
        return False

    @Shuffle.setter
    def Shuffle(self, value):
        pass

    # todo metadata
    # Q_PROPERTY(QVariantMap Metadata READ Metadata)

    @property
    def Shuffle(self):
        return False

    @Shuffle.setter
    def Shuffle(self, value):
        pass

    # def Volume
    @property
    def Volume(self):
        return 1.0

    @property
    def Position(self):
        song = self.main_window.services.current_song
        if song:
            return song.position.total_seconds * 1000
        return 0

    @property
    def MinimumRate(self):
        return 1.0

    @property
    def MaximumRate(self):
        return 1.0

    @property
    def CanGoNext(self):
        return True

    @property
    def CanGoPrevious(self):
        return True

    @property
    def CanPlay(self):
        return True

    @property
    def CanPause(self):
        return True

    @property
    def CanSeek(self):
        return False

    @property
    def CanControl(self):
        return False

    # org.mpris.MediaPlayer2.TrackList MPRIS 2.0 Player interface
    # Q_PROPERTY(TrackIds Tracks READ Tracks)
    @property
    def Tracks(self):
        return []

    def __init__(self, main_window):
        super().__init__()
        self.main_window = main_window
        self.root_adaptor = _MprisRootAdaptor(self)
        self.player_adaptor = _MprisPlayerAdaptor(self)
        if not QtDBus.QDBusConnection.sessionBus().registerService(
                self.svname):
            _logger().warning('Failed to register %s on the session bus' %
                              self.svname)
            return
        # print(QtDBus.QDBusConnection.sessionBus().registerObject('/', self))
        print(QtDBus.QDBusConnection.sessionBus().registerObject('/org/mpris/MediaPlayer2', self))
        print('MPRIS service started: ', self.Identity)

    def PlayPause(self):
        self.main_window.services.play()

    def Play(self):
        self.main_window.services.play()

    def Pause(self):
        self.main_window.services.pause()

    def Stop(self):
        self.main_window.services.play()

    def Seek(self, float):
        pass

    def SetPosition(self, track_id, pos):
        pass

    def OpenUri(self, uri):
        pass

    def Raise(self):
        self.main_window.raise_()

    def Close(self):
        self.main_window.close()


class _MprisPlayerAdaptor(QtDBus.QDBusAbstractAdaptor):
    QtCore.Q_CLASSINFO("D-Bus Interface", "org.mpris.MediaPlayer2.Player")
    QtCore.Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"org.mpris.MediaPlayer2.Player\">\n"
"    <method name=\"Next\"/>\n"
"    <method name=\"Previous\"/>\n"
"    <method name=\"Pause\"/>\n"
"    <method name=\"PlayPause\"/>\n"
"    <method name=\"Stop\"/>\n"
"    <method name=\"Play\"/>\n"
"    <method name=\"Seek\">\n"
"      <arg direction=\"in\" type=\"x\" name=\"Offset\"/>\n"
"    </method>\n"
"    <method name=\"SetPosition\">\n"
"      <arg direction=\"in\" type=\"o\" name=\"TrackId\"/>\n"
"      <arg direction=\"in\" type=\"x\" name=\"Position\"/>\n"
"    </method>\n"
"    <method name=\"OpenUri\">\n"
"      <arg direction=\"in\" type=\"s\" name=\"Uri\"/>\n"
"    </method>\n"
"    <signal name=\"Seeked\">\n"
"      <arg type=\"x\" name=\"Position\"/>\n"
"    </signal>\n"
"    <property access=\"read\" type=\"s\" name=\"PlaybackStatus\"/>\n"
"    <property access=\"readwrite\" type=\"s\" name=\"LoopStatus\"/>\n"
"    <property access=\"readwrite\" type=\"d\" name=\"Rate\"/>\n"
"    <property access=\"readwrite\" type=\"b\" name=\"Shuffle\"/>\n"
"    <property access=\"read\" type=\"a{sv}\" name=\"Metadata\">\n"
"      <annotation value=\"QVariantMap\" name=\"com.trolltech.QtDBus.QtTypeName\"/>\n"
"    </property>\n"
"    <property access=\"readwrite\" type=\"d\" name=\"Volume\"/>\n"
"    <property access=\"read\" type=\"x\" name=\"Position\"/>\n"
"    <property access=\"read\" type=\"d\" name=\"MinimumRate\"/>\n"
"    <property access=\"read\" type=\"d\" name=\"MaximumRate\"/>\n"
"    <property access=\"read\" type=\"b\" name=\"CanGoNext\"/>\n"
"    <property access=\"read\" type=\"b\" name=\"CanGoPrevious\"/>\n"
"    <property access=\"read\" type=\"b\" name=\"CanPlay\"/>\n"
"    <property access=\"read\" type=\"b\" name=\"CanPause\"/>\n"
"    <property access=\"read\" type=\"b\" name=\"CanSeek\"/>\n"
"    <property access=\"read\" type=\"b\" name=\"CanControl\"/>\n"
"  </interface>\n"
"")
    pass


class _MprisRootAdaptor(QtDBus.QDBusAbstractAdaptor):
    """ This provides the DBus adaptor to the outside world"""
    QtCore.Q_CLASSINFO("D-Bus Interface", 'org.mpris.MediaPlayer2')
    QtCore.Q_CLASSINFO("D-Bus Introspection", ""
"  <interface name=\"org.mpris.MediaPlayer2\">\n"
"    <method name=\"Raise\"/>\n"
"    <method name=\"Quit\"/>\n"
"    <property access=\"read\" type=\"b\" name=\"CanQuit\"/>\n"
"    <property access=\"read\" type=\"b\" name=\"CanRaise\"/>\n"
"    <property access=\"read\" type=\"b\" name=\"HasTrackList\"/>\n"
"    <property access=\"read\" type=\"s\" name=\"Identity\"/>\n"
"    <property access=\"read\" type=\"s\" name=\"DesktopEntry\"/>\n"
"    <property access=\"read\" type=\"as\" name=\"SupportedUriSchemes\"/>\n"
"    <property access=\"read\" type=\"as\" name=\"SupportedMimeTypes\"/>\n"
"    <property access=\"readwrite\" type=\"b\" name=\"Fullscreen\"/>\n"
"    <property access=\"read\" type=\"b\" name=\"CanSetFullscreen\"/>\n"
"  </interface>\n"
        "")


    # org.mpris.MediaPlayer2 MPRIS 2.0 Root interface
    @QtCore.pyqtProperty(bool)
    def CanRaise(self):
        return self.parent().CanRaise

    @QtCore.pyqtProperty(bool)
    def CanQuit(self):
        return self.parent().CanQuit

    @QtCore.pyqtProperty(bool)
    def HasTrackList(self):
        return self.parent().HasTrackList

    @QtCore.pyqtProperty(str)
    def Identity(self):
        return self.parent().Identity

    @QtCore.pyqtProperty(str)
    def DesktopEntry(self):
        return self.parent().DesktopEntry

    @QtCore.pyqtProperty(list)
    def SupportedUriSchemes(self):
        return self.parent().SupportedUriSchemes

    @QtCore.pyqtProperty(list)
    def SupportedMimeTypes(self):
        return self.parent().SupportedMimeTypes

    # // org.mpris.MediaPlayer2 MPRIS 2.2 Root interface
    @QtCore.pyqtProperty(bool)
    def CanSetFullscreen(self):
        return self.parent().CanSetFullscreen

    @QtCore.pyqtProperty(bool)
    def Fullscreen(self):
        return self.parent().Fullscreen

    @Fullscreen.setter
    def Fullscreen(self, value):
        self.parent().Fullscreen = value

    @QtCore.pyqtSlot()
    def Raise(self):
        self.parent().Raise()

    @QtCore.pyqtSlot()
    def Quit(self):
        self.parent().Close()
