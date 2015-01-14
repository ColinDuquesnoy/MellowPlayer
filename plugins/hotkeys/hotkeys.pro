#----------------------------------------------------------
#
# This file is part of MellowPlayer.
#
# MellowPlayer is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# MellowPlayer is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with MellowPlayer.  If not, see <http://www.gnu.org/licenses/>.
#
#----------------------------------------------------------
TEMPLATE      = lib
TARGET        = mpp_hotkeys
CONFIG       += plugin static
QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
HEADERS       = hotkeys.h
SOURCES       = hotkeys.cpp

INCLUDEPATH  += ../../lib/include
macx{
    # find and link with mellowplayer framework
    QMAKE_LFLAGS    += -F../../lib
    LIBS            += -framework mellowplayer

    # on OSX, plugins are bundled with the .app
    DESTDIR       = ../../app/MellowPlayer.app/Contents/plugins
}
win32:CONFIG(debug){
    LIBS            += -L../../lib/debug -lmellowplayer1
    DESTDIR       = ../../app/plugins
}
win32:CONFIG(release){
    LIBS            += -L../../lib/release -lmellowplayer1
    DESTDIR       = ../../app/plugins
}
unix:!macx {
    # find and link with libmellowplayer
    LIBS            += -L../../lib -lmellowplayer

    # move the plugins next to the app so that we load them when running the
    # app with qt creator (for developpers)
    DESTDIR       = ../../app/plugins
}

# Optional KDE support config
kde_support {
    message("kde support: will use KGlobalAccell for global shortcuts")
    DEFINES += "__kde_support__=1"
    QT += KGlobalAccel
}
else{
    # Build qxtglobalshortcut lib as part of our extension
    message("QxtGlobalShortcut will be used for global shortcuts")
    QXT            = core
    DEFINES       += BUILD_QXT_CORE BUILD_QXT_GUI
    INCLUDEPATH   += libqxt/src/core libqxt/src/widgets
    VPATH         += $$INCLUDEPATH
    HEADERS       += qxtglobalshortcut.h
    SOURCES       += qxtglobal.cpp qxtglobalshortcut.cpp
    unix: {
        greaterThan(QT_MAJOR_VERSION, 4): QT += gui-private
    }
    unix:!macx {
        SOURCES += x11/qxtglobalshortcut_x11.cpp
    }
    macx {
        SOURCES += mac/qxtglobalshortcut_mac.cpp
        LIBS += -framework Carbon
    }

    win32 {
        SOURCES += win/qxtglobalshortcut_win.cpp
        LIBS += -luser32
    }
}

# Setup install target
unix:!macx {
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }
    target.path = $$PREFIX/share/mellowplayer/plugins
}
win32 {
    # todo
}
INSTALLS += target
