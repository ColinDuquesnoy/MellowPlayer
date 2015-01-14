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
# This extension is built only on GNU/Linux!
TEMPLATE      = lib
TARGET        = mpp_mpris2
CONFIG       += plugin static
QT           += dbus gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
HEADERS       = mpris2.h \
                mpris2root.h \
                mpris2player.h
SOURCES       = mpris2.cpp \
                mpris2root.cpp \
                mpris2player.cpp

# find and link with libmellowplayer
INCLUDEPATH  += ../../lib/include
LIBS            += -L../../lib -lmellowplayer

# move the plugins next to the app so that we load them when running the
# app with qt creator (for developpers)
DESTDIR       = ../../app/plugins

# setup install target
isEmpty(PREFIX) {
    PREFIX = /usr/local
}
target.path = $$PREFIX/share/mellowplayer/plugins
INSTALLS += target
