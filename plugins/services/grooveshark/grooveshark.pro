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
CONFIG       += plugin
QT           += widgets webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets
HEADERS       = grooveshark.h
SOURCES       = grooveshark.cpp
TARGET        = $$qtLibraryTarget(grooveshark)
# for builtin plugins
INCLUDEPATH  += ../../../lib/include
macx{
    QMAKE_LFLAGS    += -F../../../lib
    LIBS += -framework mellowplayer
}
else{
    LIBS         += -L../../../lib -lmellowplayer
}

DESTDIR       = ../../../app/plugins/services

RESOURCES += \
    grooveshark.qrc
