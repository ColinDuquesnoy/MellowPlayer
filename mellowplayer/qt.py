"""
A Qt API selector that can be used to switch between PyQt4 and PyQt5.
"""
# Those module will be defined when calling ``setup_qt_api``
QT_API = None
QtCore = None
QtGui = None
QtWidget = None
QtDBus = None
QtWebKit = None
QtWebKitWidgets = None
QtNetwork = None
Qt = None


def setup_qt_api(qt=4):
    """
    Setup the Qt API:

    :param qt: the qt api to used: 4 or 5
    """
    global QtCore, QtGui, QtWidgets, QtWebKit, QtWebKitWidgets, QtNetwork
    global QtDBus, Qt, QT_API
    from mellowplayer import system
    if qt == 4:
        import sip
        # require the variant api to be able to send the proper data types
        # over DBUS (if we do not set that property, there is no way (AFAIK)
        # to send a string list as it is implicitely converted to QVariantList
        # (Dbus/Mpris expect a # QStringList not a QVariantList)
        sip.setapi("QVariant", 1)
        from PyQt4 import QtCore
        from PyQt4 import QtGui
        from PyQt4 import QtWebKit
        from PyQt4 import QtNetwork
        from PyQt4 import Qt
        # mimic PyQt5 layout
        QtWidgets = QtGui
        QtWebKitWidgets = QtWebKit
        if system.LINUX:
            from PyQt4 import QtDBus
        QT_API = 4
    else:
        from PyQt5 import QtCore
        from PyQt5 import QtGui
        from PyQt5 import QtWidgets
        from PyQt5 import QtWebKit
        from PyQt5 import QtWebKitWidgets
        from PyQt5 import QtNetwork
        from PyQt5 import Qt
        if system.LINUX:
            from PyQt5 import QtDBus
        QT_API = 5


def to_string(obj):
    if QT_API == 4:
        return str(obj.toString())
    return str(obj)


def to_bool(obj):
    if QT_API == 4:
        return obj.toBool()
    return eval(obj)


def to_pyobject(obj):
    if QT_API == 4:
        return obj.toPyObject()
    return obj