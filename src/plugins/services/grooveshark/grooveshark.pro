TEMPLATE      = lib
CONFIG       += plugin static
QT           += widgets
INCLUDEPATH  += ../../../../include
HEADERS       = grooveshark_plugin.h
SOURCES       = grooveshark_plugin.cpp
TARGET        = $$qtLibraryTarget(grooveshark_plugin)
DESTDIR       = ../../../../src/mellowplayer/plugins
