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
QT                 += core gui network webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

LIBS += -Lplugins \
        -lmpp_grooveshark \
        -lmpp_hotkeys \


# link with libmellowplayer
INCLUDEPATH        += ../lib/include
win32{
    LIBS += -luser32
}
win32:CONFIG(debug){
    LIBS            += -L../lib/debug -lmellowplayer
}
win32:CONFIG(release){
    LIBS            += -L../lib/release -lmellowplayer
}
unix{
    LIBS            += -L../lib -lmellowplayer\
}
macx {
   LIBS             += -framework Carbon
}
unix:!macx {
    QT              += dbus
    LIBS            += -lmpp_mpris2
}


SOURCES         += main.cpp\
                   mainwindow.cpp \
                   application.cpp \
                   singleinstancecontroller.cpp \
                   cookiejar.cpp \
                   icons.cpp \
                   pluginsmanager.cpp \
                   dlgselectservice.cpp \
                   dlgpreferences.cpp \
                   keysequenceedit.cpp
HEADERS         += mainwindow.h \
                   application.h \
                   singleinstancecontroller.h \
                   cookiejar.h \
                   icons.h \
                   pluginsmanager.h \
                   dlgselectservice.h \
                   dlgpreferences.h \
                   shortcuts.h \
                   keysequenceedit_p.h \
                   keysequenceedit.h
RESOURCES        = mellowplayer.qrc
FORMS           += mainwindow.ui \
                   dlg_select_service.ui \
                   dlg_preferences.ui

# Version infos
VERSION          = 1.0.0
DEFINES         += VERSION_MAJOR=1
DEFINES         += VERSION_MINOR=0
DEFINES         += VERSION_PATCH=0
DEFINES         += VERSION_STATUS=\\\"-alpha1\\\"


kde_support {
  # Optional KDE support will use KGlobalAccel
  QT += KGlobalAccel
}

# install
macx{
    CONFIG += app_bundle
    target.path = $$PREFIX/Applications
}
unix:!macx {
    isEmpty(PREFIX) {
        PREFIX = /usr/local
    }
    target.path = $$PREFIX/bin
}
win32 {
    target.path = dist
}

INSTALLS += target

