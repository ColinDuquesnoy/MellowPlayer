![MellowPlayer banner](/banner.png)

*MellowPlayer* is a **free**, **open source** and **cross-platform** desktop application
that runs **web-based music streaming services** in its own window and
provides **integration with your desktop** (hotkeys, multimedia keys, system tray,
notifications and more).

The software is written in **C++** using the **Qt** GUI toolkit.

*MellowPlayer is a Qt based alternative to* [NuvolaPlayer](https://tiliado.eu/nuvolaplayer/), 
*specifically crafted for KaOS/KF5.*

## Supported platforms:

The following platforms are supported:

- **GNU/Linux**
- **Mac OSX**
- **Windows**

## Supported music streaming services

- **Grooveshark**
- **Deezer**

## Features

- Minimize to system tray
- Integration with media keys on KDE SC/Plasma 5
- Hotkeys support QxtGlobalShortcut
- Mpris2 Interface (Linux only)
- System tray notifications
- Plugin based application (you can extend the app or add support for new service by writing a plugin)


## Dependencies

- **Qt5** (**Qt4** is also supported if you're running on Windows or if you're running on an old linux distribution, such as Ubuntu 12.04)
- **KGlobalAccell** and **KNotifications** (if built with ``kde_support``)


## Compilation

```
qmake
make
sudo make install
```

### Build options

- **CONFIG+=kde_support**: to build the application with kde support (media keys, tray icon).
- **PREFIX=%s**: the install prefix. Default is ``/usr/local`` on GNU/Linux and ``/`` (``/Applications``) OS X.

## Known issues

- 1) On OS X, the application might crash on exit if the audio backend is running. We have yet to investigate why this happen.

- 2) QtWebKit does not load some flash websites, such as Spotify. At the moment we are unable to provide
   support for such services. Things will probably change once the new Qt WebEngine supports flash.

- 3) Flash cannot be detected for grooveshark on Windows if compiling the app with Qt5. That's the reason
   why we still keep Qt4 support.
