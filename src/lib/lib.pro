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
TEMPLATE        = lib
TARGET          = mellowplayer
CONFIG         += static
VERSION         = 1.0.0
QT             += core gui widgets webkit network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets
INCLUDEPATH    += include
HEADERS         = include/mellowplayer.h \
                  include/mellowplayer/cookiejar.h \
                  include/mellowplayer/extensionsmanager.h \
                  include/mellowplayer/interfaces.h \
                  include/mellowplayer/player.h \
                  include/mellowplayer/pluginmetadata.h \
                  include/mellowplayer/services.h \
                  include/mellowplayer/song.h \
                  include/mellowplayer/streamingservicesmanager.h \
                  include/mellowplayer/urldownloader.h \
    include/mellowplayer/trayicon.h \
    include/mellowplayer/playbackstatus.h
SOURCES         = src/extensionsmanager.cpp \
                  src/cookiejar.cpp \
                  src/interfaces.cpp \
                  src/player.cpp \
                  src/services.cpp \
                  src/song.cpp \
                  src/streamingservicesmanager.cpp \
                  src/urldownloader.cpp \
    src/trayicon.cpp
# Optional KDE support will use KGlobalAccel
kde_support {
    QT += KNotifications
    DEFINES += "__kde_support__=1"
}

unity_support {
    DEFINES += "__unity_support__=1"
}
