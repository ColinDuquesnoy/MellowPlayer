![MellowPlayer banner](docs/_static/banner.png)

[![GNU/Linux and Mac OSX Build Status](https://travis-ci.org/ColinDuquesnoy/MellowPlayer.svg?branch=develop)](https://travis-ci.org/ColinDuquesnoy/MellowPlayer)
[![Windows Build status](https://ci.appveyor.com/api/projects/status/f65ajgawyxnxjs2a?svg=true)](https://ci.appveyor.com/project/ColinDuquesnoy/mellowplayer)
[![Coverage Status](https://coveralls.io/repos/github/ColinDuquesnoy/MellowPlayer/badge.svg?branch=develop)](https://coveralls.io/github/ColinDuquesnoy/MellowPlayer?branch=develop)
[![Latest stable release](https://img.shields.io/github/release/ColinDuquesnoy/MellowPlayer.svg)](https://github.com/ColinDuquesnoy/MellowPlayer/releases)
[![Join the chat at https://gitter.im/ColinDuquesnoy-MellowPlayer/Lobby](https://badges.gitter.im/ColinDuquesnoy-MellowPlayer/Lobby.svg)](https://gitter.im/ColinDuquesnoy-MellowPlayer/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

# About

*MellowPlayer* is a **free**, **open source** and **cross-platform** desktop application
that runs **web-based music streaming services** in its own window and
provides **integration with your desktop** (hotkeys, multimedia keys, system tray,
notifications and more).

*MellowPlayer is a Qt based alternative to* [NuvolaPlayer](https://tiliado.eu/nuvolaplayer/)
*initially crafted for* [KaOS](http://kaosx.us/). *MellowPlayer is written in C++ and QML.*

# Supported services:

| Service                                                   | GNU/Linux | AppImage | Windows | OSx | Require non-free HTML codecs | Require  flash           | Require  drm |
|-----------------------------------------------------------|-----------|----------|---------|-----|------------------------------|--------------------------|--------------|
| [Deezer](http://deezer.com)                               | Yes       | Yes      | Yes     | Yes | Yes (or flash)               | Yes (or non-free codecs) | No           |
| [Mixcloud](http://mixcloud.com)                           | Yes       | No       | No      | No  | Yes                          | No                       | No           |
| [Soundcloud](http://soundcloud.com)                       | Yes       | No       | No      | No  | Yes                          | No                       | No           |
| [Spotify](http://spotify.com)                             | Yes       | No       | No      | No  | Yes                          | No                       | Yes          |
| [TuneIn](http://tunein.com/)                              | Yes       | Yes      | Yes     | Yes | Depends on the stream        | No                       | No           |
| [8tracks](http://8tracks.com/)                            | Yes       | Yes      | Yes     | Yes | Depends on the stream        | No                       | No           |
| [Google Play Music](https://play.google.com/music/listen) | Yes       | Yes      | Yes     | Yes | ?                            | ?                        | ?            |
| [Youtube](https://youtube.com/)                           | Yes       | Yes      | Yes     | Yes | Depends on the stream        | No                       | No           |
| [Tidal](https://listen.tidal.com/)                        | Yes       | Yes      | Yes     | Yes | No                           | Yes                      | No           |
| [Anghami](https://www.anghami.com/)                       | Yes       | No       | No      | No  | Yes                          | No                       | No           |
| [Pocket Casts](https://play.pocketcasts.com/)             | Yes       | No       | No      | No  | Yes                          | No                       | No           |
| [HearThisAt](https://hearthis.at/)                        | Yes       | Yes      | Yes     | Yes | Depends on the stream        | No                       | No           |
| [Jamendo](https://www.jamendo.com/start)                  | Yes       | Yes      | Yes     | Yes | No                           | No                       | No           |
| [Radionomy](https://www.radionomy.com/)                   | Yes       | Yes      | Yes     | Yes | Depends on the stream        | No                       | No           |
| [Wynk](https://www.wynk.in/music)                         | Yes       | No       | No      | No  | Yes                          | No                       | No           |
| [ympd](https://github.com/notandy/ympd)                   | Yes       | Yes      | Yes     | Yes | No                           | No                       | No           |
| [Plex](https://www.plex.tv/)                              | Yes       | No       | No      | No  | Yes                          | No                       | ?            |
| [Youtube Music](https://music.youtube.com/)               | Yes       | Yes      | Yes     | Yes | Depends on the stream        | No                       | No           |
| [Netflix](https://www.netflix.com)                        | Yes       | No       | No      | No  | No                           | No                       | Yes          |

# Limitations:

- For licensing reason, we do not ship the flash player plugin and the widevine DRM plugins in our official releases.
- Some services (e.g. Spotify, Soundcloud and Mixcloud) also requires QtWebEngine to be compiled with proprietary codecs, which is not the case in our official releases.
- Tidal HiFi does not work because there is no MQA plugin available for chromium based browsers.

# Resources

- [Official website](https://colinduquesnoy.github.io/MellowPlayer/)
- [Documentation](http://mellowplayer.readthedocs.org/en/latest/)
- [Wiki on Github](https://github.com/ColinDuquesnoy/MellowPlayer/wiki)

# License

MellowPlayer is licensed under the GPL license.

# Download

- [Github release page](https://github.com/ColinDuquesnoy/MellowPlayer/releases)

## GNU/Linux Packages

- [Fedora](http://mellowplayer.readthedocs.io/en/latest/users/install.html#fedora)
- [Ubuntu](http://mellowplayer.readthedocs.io/en/latest/users/install.html#ubuntu-17-10)
- [openSUSE](http://mellowplayer.readthedocs.io/en/latest/users/install.html#opensuse-tumbleweed)
- [ArchLinux](http://mellowplayer.readthedocs.io/en/latest/users/install.html#archlinux)
- [KaOS](http://mellowplayer.readthedocs.io/en/latest/users/install.html#kaos)

# Requirements

## Build dependencies

- qbs >= 1.10
- a c++17 compiler (gcc6, msvc 2015 or clang)
- Qt5 (>= 5.9.0, QtWebEngine and QtQuickControls2 needed)
- Libnotify (optional, GNU/Linux only)

## Bundled 3rd-parties

### Frameworks

- [Boost.DI](http://boost-experimental.github.io/di/)
- [spdlog](https://github.com/gabime/spdlog)
- [libqxt](https://bitbucket.org/libqxt/libqxt/wiki/Home) *(QxtGlobalShortcut)*

### Testing

- [catch](https://github.com/philsquared/Catch)
- [fakeit](https://github.com/eranpeer/FakeIt)
- [lcov](https://github.com/linux-test-project/lcov)

# Compilation

Building MellowPlayer requires [Qbs](http://doc.qt.io/qbs/) >= 1.10 and a **C++17** compiler (GCC >= 6.x or Clang >= 3.5 or MSVC 2015 Update 2).

Qbs is a new build system from the Qt Company that is much easier to use compared to CMake, especially for Qt based projects.

If you want to learn more, please read the [Qbs manual](http://doc.qt.io/qbs/index.html),
especially the [setup guide](http://doc.qt.io/qbs/configuring.html) and how to install artifacts
from the [installation guide](http://doc.qt.io/qbs/installing-files.html).

## From QtCreator

Open up `mellowplayer.qbs` with QtCreator, hit build and run.

## From Command Line

Before you can build, you have to [setup qbs](http://doc.qt.io/qbs/configuring.html). This step must be done the first time you're building MellowPlayer and everytime you update your Qt version or toolchain.

### Setting up qbs

```bash
qbs-setup-toolchains --detect
qbs-setup-qt $(which qmake) qt5  # make sure that qmake is in PATH
qbs-config defaultProfile qt5
```
### Building MellowPlayer

```bash
qbs build release
```

*Note: If you're using qbs >= 1.11, replace ``release`` by ``config:release``*

#### Build options

You can append the following command line options when building MellowPlayer:

- ``projects.MellowPlayer.defaultTheme``:``<string>``: the name of the default theme. Can be set to any theme appearing in the theme combo box. Default value: "Adaptive".
- ``projects.MellowPlayer.buildTests``:``<bool>``: true to build mellowplayer test suite. Default value: false.
- ``projects.MellowPlayer.enableCoverage``:``<bool>``: true to enable code coverage build. Require a debug build config and a gcc compiler. Default value: false;

### Running MellowPlayer from build directory

```bash
qbs run config:release -p MellowPlayer
```

### Installing MellowPlayer on your system

```bash
sudo qbs install --install-root /usr/ config:release
```

# Running the test suite

Make sure you've built MellowPlayer with ``projects.MellowPlayer.buildTests:true``

```bash
qbs resolve debug projects.MellowPlayer.buildTests:true
qbs build debug projects.MellowPlayer.buildTests:true
```

To run the tests, just build one of the below products (either from QtCreator or from command line):

- ``tests``: run all tests (unit and integration tests)
- ``unit-tests``: run unit tests only
- ``integration-tests``: run integration tests only

Example from command line:

```bash
qbs build -p tests debug
```

# Contributing

MellowPlayer is an open-source application that needs your help to go on growing and improving!

There are many ways for developer and non-developers to contribute to the project. You can report (and fix) bugs, add new translations, add support for new streaming services (the core team won't support all services, especially those which are not free), and so on...

If you feel like you want to contribute to the project, make sure to checkout the [contributing guidelines](https://github.com/ColinDuquesnoy/MellowPlayer/blob/master/.github/CONTRIBUTING.md)!

