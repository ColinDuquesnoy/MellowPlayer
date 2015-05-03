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


## Resources

- [Official website](http://colinduquesnoy.github.io/MellowPlayer/)
- [Wiki](https://github.com/ColinDuquesnoy/MellowPlayer/wiki)
- [API Reference](http://colinduquesnoy.github.io/MellowPlayer/doc/index.html)

## License

MellowPlayer is licensed under the GPL license.

## Dependencies

All platforms:
- **Qt5** (>= 5.4.1)
- **flashplugin** (optional runtime dependency)

KDE Sc/Plasma 5:
- **KGlobalAccell**
- **KNotifications**

Ubuntu/Unity:
- **libnotify** (runtime dependency)
- **libdbusmenu-qt5**

Other GNU/Linux distributions/desktops:
- **libnotify** (runtime dependency)

## Compilation

```
qmake
make
sudo make install
```

Build options:

- **CONFIG+=kde_support**: to build the application with kde support (media keys, tray icon).
- **CONFIG+=unity_support**: to build the application with Unity desktop support (disable tray icon, fix global menu, unity quicklists).
- **PREFIX=%s**: the install prefix. Default is ``/usr`` on GNU/Linux and ``/`` (``/Applications``) OS X.

## Contributing

MellowPlayer is an open-source application that needs your help to go on growing and improving!

There are many ways for developer and non-developers to contribute to the project. You can report (and fix) bugs, add new translations, add support for new streaming services (the core team won't support all services, especially those which are not free), and so on...

If you feel like you want to contribute to the project, make sure to checkout the [contributing guidelines](https://github.com/ColinDuquesnoy/MellowPlayer/blob/master/CONTRIBUTING.md) and the [wiki](https://github.com/ColinDuquesnoy/MellowPlayer/wiki)!
