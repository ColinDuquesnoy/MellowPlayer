 QT += core gui webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

# Optional KDE support config
KDE_SUPPORT {
  DEFINES += "__KDE_SUPPORT__=1"
  QT += KGlobalAccel
}

TARGET = MellowPlayer
TEMPLATE = app


QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
           mainwindow.cpp \
           player.cpp

INCLUDEPATH += ../../include

HEADERS  += ../../include/mainwindow.h \
            ../../include/player.h \
            ../../include/plugins.h

#LIBS += -Lplugins -lgrooveshark_plugin

FORMS    += ../../data/forms/mainwindow.ui\
            ../../data/forms/dlg_select_service.ui

RESOURCES = ../../data/mellowplayer.qrc
