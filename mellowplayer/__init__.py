"""
**MellowPlayer** is a free and cross-platform desktop application that runs a
web interface of **cloud music services** in its own window and provides
**integration with your desktop** (multimedia keys, system tray,
notifications and more).

"""
import sip
# sip api v1 is required to properly send dbus notification (otherwise the
# arguments do not have the correct type (this issue is mainly related to how
# api v2 autointerpret list, it does not generate QStringList)
sip.setapi("QString", 1)
sip.setapi("QVariant", 1)

__version__ = '1.0a1'
