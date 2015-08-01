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
TARGET              = MellowPlayer
TEMPLATE            = app
QT                 += core gui network webkit widgets webkitwidgets

# Add static plugins here (and in main.cpp)
LIBS += -L.
LIBS += -lmpp_rdio
LIBS += -lmpp_soundcloud
LIBS += -lmpp_mixcloud
LIBS += -lmpp_deezer
LIBS += -lmpp_hotkeys
LIBS += -lmpp_notifications

win32 { # force relink app when a static lib changed.
    PRE_TARGETDEPS += mpp_rdio.lib
    PRE_TARGETDEPS += mpp_soundcloud.lib
    PRE_TARGETDEPS += mpp_mixcloud.lib
    PRE_TARGETDEPS += mpp_deezer.lib
    PRE_TARGETDEPS += mpp_hotkeys.lib
    PRE_TARGETDEPS += mpp_notifications.lib
}
else { # force relink app when a static lib changed.
    PRE_TARGETDEPS += libmpp_rdio.a
    PRE_TARGETDEPS += libmpp_soundcloud.a
    PRE_TARGETDEPS += libmpp_mixcloud.a
    PRE_TARGETDEPS += libmpp_deezer.a
    PRE_TARGETDEPS += libmpp_hotkeys.a
    PRE_TARGETDEPS += libmpp_notifications.a
}

# link with libmellowplayer
INCLUDEPATH        += ../lib/include
win32:RC_FILE     += MellowPlayer.rc
win32{
    LIBS += -luser32
}
win32:CONFIG(Debug){
    LIBS            += -L../lib/debug -lmellowplayer
    PRE_TARGETDEPS += ../lib/debug/mellowplayer.lib
}
win32:CONFIG(Release){
    LIBS            += -L../lib/release -lmellowplayer
    PRE_TARGETDEPS += ../lib/release/mellowplayer.lib
}
unix{
    LIBS            += -L../lib -lmellowplayer
    PRE_TARGETDEPS  += ../lib/libmellowplayer.a
}
macx {
   LIBS             += -framework Carbon -lcrypto -lssl
   ICON              = icons/mellowplayer.icns
}
unix:!macx {
    QT              += dbus

    # linux only plugins and libraries
    LIBS            += -lmpp_mpris2 -lX11
    LIBS            += -lmpp_gnomemediakeys
    PRE_TARGETDEPS  += libmpp_mpris2.a
    PRE_TARGETDEPS  += libmpp_gnomemediakeys.a
}


SOURCES         += main.cpp\
                   mainwindow.cpp \
                   application.cpp \
                   singleinstancecontroller.cpp \
                   icons.cpp \
                   pluginsmanager.cpp \
                   dlgselectservice.cpp \
                   dlgpreferences.cpp \
                   webview.cpp
HEADERS         += mainwindow.h \
                   application.h \
                   singleinstancecontroller.h \
                   icons.h \
                   pluginsmanager.h \
                   dlgselectservice.h \
                   dlgpreferences.h \
                   shortcuts.h \
                   webview.h
RESOURCES        = mellowplayer.qrc
FORMS           += mainwindow.ui \
                   dlg_select_service.ui \
                   dlg_preferences.ui

# Version infos
VERSION          = 1.5.0
DEFINES         += VERSION_MAJOR=1
DEFINES         += VERSION_MINOR=5
DEFINES         += VERSION_MICRO=0
DEFINES         += VERSION_STATUS=\\\"\\\"


# Optional KDE support will use KGlobalAccel
kde_support {
    QT += KGlobalAccel KNotifications
    DEFINES += "__kde_support__=1"
}

unity_support {
    DEFINES += "__unity_support__=1"
    INCLUDEPATH += /usr/include/dbusmenu-qt5/
    LIBS += -ldbusmenu-qt5
}

# install
macx{
    CONFIG += app_bundle
    target.path = $$PREFIX/Applications
}
unix:!macx {
    isEmpty(PREFIX) {
        PREFIX = /usr
    }
    target.path = $$PREFIX/bin
}
win32 {
    target.path = dist
}

INSTALLS += target
