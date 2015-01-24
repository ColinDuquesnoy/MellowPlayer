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
app.depends     = plugins lib
plugins.depends = lib

unix{
    # install application desktop file
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }
    desktopfile.path = $$PREFIX/share/applications
    desktopfile.files = share/mellowplayer.desktop
    INSTALLS += desktopfile

    iconfile.path = $$PREFIX/share/pixmaps
    iconfile.files = app/icons/mellowplayer.png
    INSTALLS += iconfile
}

# automatically release translations, .qm files are embedded
# in the application resources.
system("lrelease MellowPlayer.pro")

# translations for the whole project (including plugins and lib) are stored
# in the app folder (for an easier integration with the app's resources).
TRANSLATIONS += app/translations/mellowplayer_fr.ts
