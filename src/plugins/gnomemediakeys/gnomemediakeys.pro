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

# This extension is built on GNU/Linux only!
TEMPLATE      = lib
TARGET        = mpp_gnomemediakeys
CONFIG       += plugin static
QT           += dbus gui widgets
HEADERS       = gnomemediakeys.h
SOURCES       = gnomemediakeys.cpp
INCLUDEPATH  += ../../lib/include
LIBS         += -L../../lib -lmellowplayer
DESTDIR       = ../../app

kde_support {
    # plugin does not do anything on KDE
    DEFINES += "__kde_support__=1"
}

DBUS_INTERFACES += org.gnome.SettingsDaemon.MediaKeys.xml
