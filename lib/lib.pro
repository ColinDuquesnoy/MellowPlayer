TEMPLATE      = lib
QT           += widgets webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets
HEADERS       = mellowplayer/plugins.h
SOURCES       = plugins.cpp
TARGET        = $$qtLibraryTarget(mellowplayer)
