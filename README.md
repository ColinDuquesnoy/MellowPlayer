[![Build status](https://gitlab.com/ColinDuquesnoy/MellowPlayer/badges/develop/build.svg)](https://gitlab.com/ColinDuquesnoy/MellowPlayer/commits/develop)
[![Coverage report](https://gitlab.com/ColinDuquesnoy/MellowPlayer/badges/develop/coverage.svg)](https://gitlab.com/ColinDuquesnoy/MellowPlayer/commits/develop)
[![Release](https://img.shields.io/github/release/ColinDuquesnoy/MellowPlayer.svg)](https://github.com/ColinDuquesnoy/MellowPlayer/releases)

## About

*MellowPlayer* is a **free**, **open source** and **cross-platform** desktop application
that runs **web-based music streaming services** in its own window and
provides **integration with your desktop** (hotkeys, multimedia keys, system tray,
notifications and more).

*MellowPlayer is a Qt based alternative to* [NuvolaPlayer](https://tiliado.eu/nuvolaplayer/),
*specifically crafted for* [KaOS](http://kaosx.us/).

## Supported services:

- [Deezer](http://deezer.com)
- [Mixcloud](http://mixcloud.com)
- [Soundcloud](http://soundcloud.com)
- [Spotify](http://spotify.com)
- [TuneIn](http://tunein.com/)
- [8tracks](http://8tracks.com/)
- [Google Play Music](https://play.google.com/music/listen)


## Resources

- [Official website](https://colinduquesnoy.github.io/MellowPlayer/)
- [Documentation](http://mellowplayer.readthedocs.org/en/webengine/)

## License

MellowPlayer is licensed under the GPL license.

## Dependencies

- **Qt5** (>= 5.6.0)
- **SnoreNotify** (>= 0.7.0)
- **PepperFlash** (runtime dependency)


## Compilation

```
mkdir build && cd build
qmake ..
make
sudo make install
```

## Contributing

MellowPlayer is an open-source application that needs your help to go on growing and improving!

There are many ways for developer and non-developers to contribute to the project. You can report (and fix) bugs, add new translations, add support for new streaming services (the core team won't support all services, especially those which are not free), and so on...

If you feel like you want to contribute to the project, make sure to checkout the [contributing guidelines](https://github.com/ColinDuquesnoy/MellowPlayer/blob/master/CONTRIBUTING.rst)!
