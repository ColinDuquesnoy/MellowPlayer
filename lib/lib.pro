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
TARGET        = $$qtLibraryTarget(mellowplayer)
VERSION       = 1.0.0
QT           += widgets webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets
INCLUDEPATH  += include
HEADERS       = include/mellowplayer.h \
                include/mellowplayer/plugins.h \
                include/mellowplayer/cloudservicesmanager.h \
                include/mellowplayer/services.h \
    include/mellowplayer/song.h \
    include/mellowplayer/player.h
SOURCES       = src/plugins.cpp \
                src/cloudservicesmanager.cpp \
                src/services.cpp \
    src/song.cpp \
    src/player.cpp

macx{
    CONFIG += lib_bundle
    FRAMEWORK_HEADERS.version = Versions
    FRAMEWORK_HEADERS.files = $$HEADERS
    FRAMEWORK_HEADERS.path = include
    QMAKE_BUNDLE_DATA += FRAMEWORK_HEADERS
}