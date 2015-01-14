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
TARGET        = mpp_grooveshark
CONFIG       += plugin
HEADERS       = grooveshark.h
SOURCES       = grooveshark.cpp
RESOURCES    += grooveshark.qrc

INCLUDEPATH  += ../../lib/include  # libmellowplayer include path
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

    # move the plugins next to the app so that we can load them when
    # running the app with qt creator (for developpers)
    DESTDIR       = ../../app/plugins
}

unix:!macx {
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }
    target.path = $$PREFIX/share/mellowplayer/plugins
}
INSTALLS += target
