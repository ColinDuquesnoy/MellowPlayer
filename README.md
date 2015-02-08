![MellowPlayer banner](/banner.png)


[![Build Status](https://travis-ci.org/ColinDuquesnoy/MellowPlayer.svg?branch=master)](https://travis-ci.org/ColinDuquesnoy/MellowPlayer)
[![Release](https://img.shields.io/github/release/ColinDuquesnoy/MellowPlayer.svg)](https://github.com/ColinDuquesnoy/MellowPlayer/releases)

## About



*MellowPlayer* is a **free**, **open source** and **cross-platform** desktop application
that runs **web-based music streaming services** in its own window and
provides **integration with your desktop** (hotkeys, multimedia keys, system tray,
notifications and more).

*MellowPlayer is a Qt based alternative to* [NuvolaPlayer](https://tiliado.eu/nuvolaplayer/),
*specifically crafted for* [KaOS](http://kaosx.us/).

![MellowPlayer](doc/_static/mellowplayer-kaos.png "MellowPlayer on KaOS (Plasma5)")

## License

MellowPlayer is licensed under the GPL license.

## Dependencies

### All platforms

- **Qt5** (>= 5.4.0) or **Qt4**
- **flashplugin** (runtime dependency)

### GNU/Linux

- **libnotify** (runtime dependency)

### KDE Sc/Plasma 5

- **KGlobalAccell**
- **KNotifications**


## Compilation

```
qmake
make
sudo make install
```

### Build options

- **CONFIG+=kde_support**: to build the application with kde support (media keys, tray icon).
- **PREFIX=%s**: the install prefix. Default is ``/usr`` on GNU/Linux and ``/`` (``/Applications``) OS X.

## Contributing

MellowPlayer is an open-source application that needs your help to go on growing and improving!

There are many ways for developer and non-developers to contribute to the project. You can report (and fix) bugs, add new translations, add support for new streaming services (the core team won't support all services, especially those which are not free), and so on...

If you feel like you want to contribute to the project, make sure to checkout the [contributing guidelines](https://github.com/ColinDuquesnoy/MellowPlayer/blob/master/CONTRIBUTING.md) and the [wiki](https://github.com/ColinDuquesnoy/MellowPlayer/wiki)!

## Known issues

- 1) On OS X, the application might crash on exit if the audio backend is running. We have yet to investigate why this happen.

- 2) QtWebKit does not load some flash websites, such as Spotify. At the moment we are unable to provide
   support for such services. Things will probably change once the new Qt WebEngine supports flash.

- 3) Flash cannot be detected for grooveshark on Windows if compiling the app with Qt5. That's the reason
   why we still keep Qt4 support.

- 4) Media Player keys cannot be used for shortcuts on OSX. On Windows they will work if you don't have another app that is using them (e.g. you might need to uninstall Windows Media Player for the media keys to be recognized by MellowPlayer). On Linux (not KDE), your best bet is to use an MPRIS2 client. On KDE, media keys should work out of the box (unless they are used by another running KDE media player such as Amarok), you can configure them in K System Settings -> Shortcuts -> Global Shortcut -> MellowPlayer component.
