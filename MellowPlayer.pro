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

TEMPLATE        = subdirs
SUBDIRS         = app \     # MellowPlayer executable
                  lib \     # MellowPlayer library (shared object/dll)
                  plugins   # plugins (shared objects/dll)
# the lib is used by both the application and the various plugins
# build it first!
app.depends     = lib
plugins.depends = lib
