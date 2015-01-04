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
TARGET        = mellowplayer
VERSION       = 1.0.0
QT           += widgets webkit network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets
INCLUDEPATH  += include
HEADERS       = include/mellowplayer.h \
                include/mellowplayer/plugins.h \
                include/mellowplayer/cloudservicesmanager.h \
                include/mellowplayer/extensionsmanager.h \
                include/mellowplayer/services.h \
                include/mellowplayer/song.h \
                include/mellowplayer/player.h \
    include/mellowplayer/urldownloader.h
SOURCES       = src/plugins.cpp \
                src/cloudservicesmanager.cpp \
                src/extensionsmanager.cpp \
                src/services.cpp \
                src/song.cpp \
                src/player.cpp \
    src/urldownloader.cpp

macx{
    CONFIG += lib_bundle
    FRAMEWORK_HEADERS.version = Versions
    FRAMEWORK_HEADERS.files = $$HEADERS
    FRAMEWORK_HEADERS.path = include
    QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS
    target.path = $$PREFIX/Library/Frameworks
}
unix:!macx {
    isEmpty(PREFIX) {
       PREFIX = /usr/local
    }
    target.path = $$PREFIX/lib
}
win32
{
    # todo
}
INSTALLS += target

