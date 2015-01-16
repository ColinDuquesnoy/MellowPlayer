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
TARGET        = mpp_hotkeys
QT           += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG       += plugin static
HEADERS       = hotkeys.h
SOURCES       = hotkeys.cpp
INCLUDEPATH  += ../../lib/include
DESTDIR       = ../../app

# Optional KDE support config
kde_support {
    message("HotkeysPlugin: kde support enabled (using KGlobalAccell)")
    DEFINES += "__kde_support__=1"
    QT += KGlobalAccel
}
else{
    # Build qxtglobalshortcut lib as part of our extension
    message("QxtGlobalShortcut will be used for global shortcuts")
    QXT            = core
    DEFINES       += BUILD_QXT_CORE BUILD_QXT_GUI
    INCLUDEPATH   += libqxt/src/core libqxt/src/widgets
    VPATH         += $$INCLUDEPATH
    HEADERS       += qxtglobalshortcut.h
    SOURCES       += qxtglobal.cpp qxtglobalshortcut.cpp
    unix: {
        greaterThan(QT_MAJOR_VERSION, 4): QT += gui-private
    }
    unix:!macx {
        SOURCES += x11/qxtglobalshortcut_x11.cpp
    }
    macx {
        SOURCES += mac/qxtglobalshortcut_mac.cpp
    }

    win32 {
        SOURCES += win/qxtglobalshortcut_win.cpp
    }
}
