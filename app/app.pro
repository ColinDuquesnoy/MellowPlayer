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
TARGET           = MellowPlayer
TEMPLATE         = app
QT              += core gui network webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets
INCLUDEPATH     += ../lib/include
macx{
    QMAKE_LFLAGS    += -F../lib
    LIBS += -framework mellowplayer
}
else{
    LIBS            += -L../lib -lmellowplayer
}
SOURCES         += main.cpp\
                   mainwindow.cpp \
                   application.cpp \
                   singleinstancecontroller.cpp \
    pluginmanager.cpp \
    cookiejar.cpp
HEADERS         += mainwindow.h \
                   application.h \
                   singleinstancecontroller.h \
    pluginmanager.h \
    cookiejar.h
RESOURCES       = mellowplayer.qrc
FORMS           += mainwindow.ui \
                   dlg_select_service.ui

# Version infos
VERSION          = 1.0.0
DEFINES         += VERSION_MAJOR=1
DEFINES         += VERSION_MINOR=0
DEFINES         += VERSION_PATCH=0
DEFINES         += VERSION_STATUS=\\\"-alpha1\\\"

# Optional KDE support config
kde_support {
  message("Building for KDE")
  DEFINES += "__kde_support__=1"
  QT += KGlobalAccel
}
