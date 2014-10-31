About
-----

**MellowPlayer** is a free, open source and cross-platform desktop application
that runs a web interface of **cloud music services** in its own window and
provides **integration with your desktop** (multimedia keys, system tray,
notifications and more).

**MellowPlayer has been heavily inspired by** `NuvolaPlayer`_.

The software is written in Python3 using the PyQt4 GUI toolkit.

Status
------

This software is under heavy development. Some parts of the GUI and some features have not been implemented yet but
you can already use it on linux and use the Grooveshark service.

The following features are already working:

- grooveshark integration
- cookies management
- MPRIS support
- global shortcuts support

This has been tested on Manjaro Linux and KaOS only.

Supported platforms:
--------------------

The following platforms will be supported:

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

At the moment you have to run the app from source checkout, just run ``bootstap.py`` with a **python3** interpreter.

.. links:

.. _NuvolaPlayer: http://nuvolaplayer.fenryxo.cz/home.html
