.. image:: https://raw.githubusercontent.com/ColinDuquesnoy/MellowPlayer/master/share/icons/mellowplayer-banner.png

*MellowPlayer* is a free, open source and cross-platform desktop application
that runs a web interface of **cloud music services** in its own window and
provides **integration with your desktop** (multimedia keys, system tray,
notifications and more).

The software is written in Python3 using the PyQt GUI toolkit.

*MellowPlayer has been heavily inspired by* `NuvolaPlayer`_.

Status
------

This software is under heavy development. Some parts of the GUI and some features have not been implemented yet but
you can already use it on linux and use the Grooveshark service.

The following features are already working:

- grooveshark integration
- cookies management
- `MPRIS 2`_ support
- global shortcuts support

This has been tested on GNU/Linux (Manjaro Linux and KaOS) and Windows 7.

Supported platforms:
--------------------

The following platforms will be supported:

- GNU/Linux
- Windows

Supported Services
------------------

At the moment, there is only one cloud music service: **Grooveshark**.

Feel free to request support for new services by opening an issue on the bug
tracker or by submitting a pull request! See the `Service Integration API`_.


Dependencies
------------

Requirements:

- Python 3 (>= 3.4)
- PyQt4 or PyQt5


Optional:

- PyGlobalShortcuts: global shortcuts (hotkeys) support


Installation
------------

At the moment, you have to run from source checkout::

    python3 bootstrap.py

You can specify the target qt api (PyQt4 or PyQt5) using the ``--qt`` command
line option. By default, Mellow Player will try to use PyQt4. E.g.::

    python3 bootstrap.py --qt=5

Please note that PyQt5 should be avoided on Linux, there are some bugs with the
QtWebKit (the app will crash as soon as you move to the next song).

.. links:

.. _NuvolaPlayer: http://nuvolaplayer.fenryxo.cz/home.html
.. _MPRIS 2: http://specifications.freedesktop.org/mpris-spec/latest/
