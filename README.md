*MellowPlayer* is a free, open source and cross-platform desktop application
that runs a web interface of **cloud music services** in its own window and
provides **integration with your desktop** (multimedia keys, system tray,
notifications and more).

The software is written in **C++** using the **Qt5** GUI toolkit.

*MellowPlayer is a qt based alternative to [NuvolaPlayer](https://tiliado.eu/nuvolaplayer/). 
It has been specifically designed to run on a KDE platform (i.e. there are more features on kde than on any other platforms)*


## Status

This software is under heavy development. Some parts of the GUI and some features have not been implemented yet but
you can already use it on linux and use the Grooveshark service.

The following features are already working:

- Grooveshark integration
- Cookies management
- [MPRIS 2](http://specifications.freedesktop.org/mpris-spec/latest/) support
- Global shortcuts support

This has been tested on KaOS plasma-next (kde5) and OS X Yosemite.

## Supported platforms:

The following platforms will be supported:

- GNU/Linux
- OSX
- Windows

## Supported Services

At the moment, there is only one cloud music service: **Grooveshark**.

Feel free to request support for new services by opening an issue on the bug
tracker or by submitting a pull request! See the [Service Integration API]() (which is not ready yet).


## Dependencies

- Qt5
- KGlobalAccell (on kde5 only)


## Compilation

```
qmake
make 
```

### Build options

- **CONFIG+=kde_support**: to build the application with kde5 support (media keys and notifications).
- **PREFIX=%s**: the install prefix. Default is ``/usr/local`` on GNU/Linux and ``/`` (``/Applications``, ``/Frameworks``) on OS X.


## Installation

``` make install ```

## Known issues

1) On OS X, the application might crash on exit if the audio backend is running. We have yet to investigate why this happen.
