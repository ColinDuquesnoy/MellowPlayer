About
-----

**MellowPlayer** is a free, open source and cross-platform desktop application
that runs a web interface of **cloud music services** in its own window and
provides **integration with your desktop** (multimedia keys, system tray,
notifications and more).

**MellowPlayer has been heavily inspired by** `NuvolaPlayer`_.

The software is written in Python3 using the PyQt4 GUI toolkit.

Supported platforms:
--------------------
- GNU/Linux
- Windows
- Mac OSX

Supported Services
------------------

At the moment, there is only one cloud music service: **Grooveshark**.

Feel free to request support for new services by opening an issue on the bug
tracker or by submitting a pull request! See the `Service Integration API`_.


Dependencies
------------

Requirements:

- Python 3 (>= 3.4)
- PyQt4


Optional:

- PyGlobalShortcuts: global shortcuts (hotkeys) support


Installation
------------
::

    pip3 install mellowplayer

Notes
-----

MellowPlayer is an alternative to `NuvolaPlayer`_ specifically created for
the `KaOS`_ distribution. *KaOS* is a pure KDE distribution that does not have
(and will never have) the GTK packages needed to run NuvolaPlayer.

The player has been designed for an integration into Qt based desktops (KDE or
LxQt), and will run well on classic desktops that still have a system tray (
XFCE, Cinnamon, OpenBox,...).

We do not recommend to use that application on a Gnome Shell or Unity desktop (
use `NuvolaPlayer`_ instead).

.. links:

.. _KaOS: http://kaosx.us/
.. _NuvolaPlayer: http://nuvolaplayer.fenryxo.cz/home.html
