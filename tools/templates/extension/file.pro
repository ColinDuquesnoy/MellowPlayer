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
TARGET        = mpp_%(name)s
CONFIG       += plugin static
QT           += gui widgets
HEADERS       = %(name)s.h
SOURCES       = %(name)s.cpp
INCLUDEPATH  += ../../lib/include
LIBS         += -L../../lib -lmellowplayer
DESTDIR       = ../../app
