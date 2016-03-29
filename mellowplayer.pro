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

# Project configuration
unix:!macx {
    TARGET = mellowplayer
}
else {
    TARGET = MellowPlayer
}
TEMPLATE = app
QT += core gui network widgets webengine webenginewidgets
!macx {
    QT += LibsnoreQt5
}
CONFIG += c++11

# Version and windows icon
win32:VERSION = 2.0.0.0 # major.minor.patch.build
else:VERSION = 2.0.0    # major.minor[.patch]
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

# Windows specific rules
win32{
    LIBS += -luser32
    RC_ICONS = app/icons/mellowplayer.ico
}

# Mac OSX specific Rules
macx {
   LIBS += -framework Carbon -lcrypto -lssl
   ICON = app/icons/mellowplayer.icns
}

# GNU/Linux specific rules
unix:!macx {
    QT += dbus
    SOURCES += utils/mpris2root.cpp \
               utils/mpris2player.cpp \
               utils/mpris_utils.cpp
    HEADERS += utils/mpris2root.h \
               utils/mpris2player.h \
               utils/mpris_utils.h
}

INCLUDEPATH   += app/include
VPATH         += app/src

# Sources, headers, resources and forms
SOURCES += main.cpp\
           application.cpp \
           controllers/base.cpp \
           controllers/hotkeys.cpp \
           controllers/notifications.cpp \
           controllers/mpris2.cpp \
           controllers/player.cpp \
           controllers/services.cpp \
           controllers/update.cpp \
           utils/icons.cpp \
           utils/playerinfo.cpp \
           utils/singleinstancecontroller.cpp \
           utils/songinfo.cpp \
           views/hoverable_button.cpp \
           views/dlgselectservice.cpp \
           views/dlgpreferences.cpp \
           views/mainwindow.cpp \
           views/webview.cpp \
           views/wizard_new_plugin.cpp

HEADERS += application.h \
           controllers/hotkeys.h \
           controllers/base.h \
           controllers/mpris2.h \
           controllers/notifications.h \
           controllers/player.h \
           controllers/services.h \
           controllers/update.h \
           utils/icons.h \
           utils/playerinfo.h \
           utils/shortcuts.h \
           utils/singleinstancecontroller.h \
           utils/songinfo.h \
           views/hoverable_button.h \
           views/dlgselectservice.h \
           views/dlgpreferences.h \
           views/mainwindow.h \
           views/webview.h \
           views/wizard_new_plugin.h

RESOURCES = app/mellowplayer.qrc
FORMS += app/forms/dlg_select_service.ui \
         app/forms/dlg_preferences.ui \
         app/forms/mainwindow.ui \
         app/forms/wizard_new_plugin.ui

# Build qxtglobalshortcut lib as part of our extension
message("QxtGlobalShortcut will be used for global shortcuts")
QXT            = core
DEFINES       += BUILD_QXT_CORE BUILD_QXT_GUI
INCLUDEPATH   += extlibs/libqxt/src/core extlibs/libqxt/src/widgets
VPATH         += $$INCLUDEPATH
HEADERS       += qxtglobalshortcut.h
SOURCES       += qxtglobal.cpp qxtglobalshortcut.cpp
unix: {
    QT += gui-private
}
unix:!macx {
    SOURCES += x11/qxtglobalshortcut_x11.cpp
    LIBS += -lX11
}
macx {
    SOURCES += mac/qxtglobalshortcut_mac.cpp
}

win32 {
    SOURCES += win/qxtglobalshortcut_win.cpp
}


# Install rules
macx{
    CONFIG += app_bundle
    target.path = $$PREFIX/Applications
}
unix:!macx {
    target.path = /usr/bin

    INSTALLS += target

    desktopfiles.path = /usr/share
    desktopfiles.files = share/applications
    INSTALLS += desktopfiles

    iconfiles.path = /usr/share
    iconfiles.files = share/icons
    INSTALLS += iconfiles

    # Install streaming services plugins
    services.path = /usr/share/mellowplayer/
    services.files = plugins
    INSTALLS += services
}
win32 {
    target.path = dist
}

# translations for the whole project (including plugins and lib) are stored
# in the app folder (for an easier integration with the app's resources).
TRANSLATIONS += app/translations/mellowplayer_en.ts \
                app/translations/mellowplayer_fr.ts \

# automatically release translations, .qm files are embedded
# in the application resources.
unix:!macx{
    system("lrelease-qt5 mellowplayer.pro")
}
else{
    system("lrelease mellowplayer.pro")
}
