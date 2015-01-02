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
HEADERS       = mpris2.h
SOURCES       = mpris2.cpp
TARGET        = mlp_mpris2
# for builtin plugins
INCLUDEPATH  += ../../lib/include
macx{
    QMAKE_LFLAGS    += -F../../lib
    LIBS            += -framework mellowplayer
}
else{
    LIBS            += -L../../lib -lmellowplayer
}

DESTDIR       = ../../app/plugins

# Optional KDE support config
kde_support {
    message("Building for KDE")
    DEFINES += "__kde_support__=1"
    QT += KGlobalAccel
}

macx{
    # todo
}
unix{
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }
    target.path = $$PREFIX/share/mellowplayer/plugins
}
win32
{
    # todo
}
INSTALLS += target
