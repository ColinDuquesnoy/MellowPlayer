QT              += core gui webkit
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets
TARGET           = MellowPlayer
TEMPLATE         = app
SOURCES         += main.cpp\
                   mainwindow.cpp
INCLUDEPATH     += ../lib
HEADERS         += mainwindow.h
FORMS           += mainwindow.ui \
                   dlg_select_service.ui
LIBS            += -L../lib -lmellowplayer
RESOURCES       = mellowplayer.qrc
# Optional KDE support config
KDE_SUPPORT {
  DEFINES += "__KDE_SUPPORT__=1"
  QT += KGlobalAccel
}
