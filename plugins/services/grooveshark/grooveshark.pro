TEMPLATE      = lib
CONFIG       += plugin
QT           += widgets webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets
HEADERS       = grooveshark.h
SOURCES       = grooveshark.cpp
TARGET        = $$qtLibraryTarget(grooveshark)
# for builtin plugins
INCLUDEPATH  += ../../../lib
LIBS         += -L../../../lib -lmellowplayer
DESTDIR       = ../../../app/plugins/services
