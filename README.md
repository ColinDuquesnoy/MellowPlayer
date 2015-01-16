![MellowPlayer banner](/banner.png)

*MellowPlayer* is a **free**, **open source** and **cross-platform** desktop application
that runs **web-based music streaming services** in its own window and
provides **integration with your desktop** (hotkeys, multimedia keys, system tray,
notifications and more).

The software is written in **C++** using the **Qt** GUI toolkit.

*MellowPlayer is a Qt based alternative to* [NuvolaPlayer](https://tiliado.eu/nuvolaplayer/), 
*specifically crafted for KaOS/KF5.*

## Development status

The application is under heavy development and the API has not been stabilized yet.

The following features are already working:

- Grooveshark service integration
- Cookies management
- [MPRIS 2](http://specifications.freedesktop.org/mpris-spec/latest/) support
- Global shortcuts support (using KGlobalAccell on KDE and QxtGlobalShortcut everywhere else).

The application has been tested on KaOS KF5, Manjaro XFCE, OS X Yosemite and Windows 7.1.

## Supported platforms:

The following platforms are supported:

- **GNU/Linux**
- **Mac OSX**
- **Windows**

*It is worth noting that even though the app is cross-platform, the focus will always be 
on the KDE linux desktop (and maybe on other Qt based desktops such as LxQt).*

## Supported Streaming Services

Here are the currently supported streaming services:

  - **Grooveshark**

## Contributing

There are many ways to contribute to MellowPlayer:

### 1) Add support for a new streaming service

Support for new streaming service is added by writing a [writing a service integration plugin]()

### 2) Extend the application

You can extend the application by [writing a generic extension plugin]().

### 3) Help with translations

See the [translators tutorial]() for more information.

### 4) Report bugs

If you found a bug in the application, please report it on our issue tracker. The application 
has a menu for easily do that (Help->Report a bug). Please, read [CONTRIBUTING.md]() before
reporting a bug!


## Dependencies

- **Qt5** (**Qt4** is also supported if you're running on Windows or if you're running on an old linux distribution, such as Ubuntu 12.04)
- **KGlobalAccell** (if built with ``kde_support``)


## Compilation

```
qmake
make 
```

### Build options

- **CONFIG+=kde_support**: to build the application with kde support (media keys, tray icon).
- **PREFIX=%s**: the install prefix. Default is ``/usr/local`` on GNU/Linux and ``/`` (``/Applications``) OS X.


## Installation

``` (sudo) make install ```

## Known issues

1) On OS X, the application might crash on exit if the audio backend is running. We have yet to investigate why this happen.
2) QtWebKit does not load some flash websites, such as Spotify. At the moment we are unable to provide
   support for such services. Things will probably change once the new Qt WebEngine supports flash.
3) Flash cannot be detected for grooveshark on Windows if compiling the app with Qt5. That's the reason
   why we still keep Qt4 support.
