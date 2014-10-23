About
-----

**MellowPlayer** is a free, open source and cross-platform desktop application
that runs a web interface of **cloud music services** in its own window and
provides **integration with your desktop** (multimedia keys, system tray,
notifications and more).

The software is written in Python3 using the PyQt5 GUI toolkit.

*MellowPlayer has been heavily inspired by* `NuvolaPlayer`_.

Supported platforms:
--------------------
- GNU/Linux
- Windows
- Mac OSX

Supported Services
------------------

At the moment, there is only one officially supported cloud music service:
**Grooveshark**.

To add support for your favorite cloud music service,
`write a service integration plugin`_.


Requirements
------------

- Python 3 (>= 3.4)
- PyQt5


Installation
------------

To install the application on your system, you must first install **Python3**,
**PyQt5** and **pip3** using your package manager. Then run::

    pip3 install mellowplayer

Alternatively, you can just clone the repository and run the bootstrap script
to check it out without installing.

Motivations & Initial Goals
---------------------------

MellowPlayer is an alternative to `NuvolaPlayer`_ specifically created for
the `KaOS`_ distribution. *KaOS* is a pure KDE distribution that does not have
the GTK packages needed to run NuvolaPlayer and I really missed that app. Also
NuvolaPlayer is a Linux only application and, AFAIK, there is no equivalent for
other platforms such as Windows or Mac OSX. So I decided to roll my own
solution.

The initial goal is to create a standalone application that can connect to the
Grooveshark service and run it in its on window on the desktop or in the system
tray with multimedia keys integration. Ideally it should be possible to easily
integrate new cloud music services by writing python plugins. The application
has been designed with this goal in mind, e.g. there is already a service
chooser dialog even though there is only one service.

The player has been designed for an integration into Qt based desktops
(KDE or LxQt), and will run well on classic desktops that still have a system
tray (XFCE, Cinnamon, OpenBox,...). Integration with more esoteric desktops
such as Unity or Gnome Shell is not supported, at least in the first time.


.. links:

.. _KaOS: http://kaosx.us/
.. _NuvolaPlayer: http://nuvolaplayer.fenryxo.cz/home.html
