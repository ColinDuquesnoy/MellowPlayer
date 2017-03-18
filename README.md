[![Build status](https://gitlab.com/ColinDuquesnoy/MellowPlayer/badges/develop/build.svg)](https://gitlab.com/ColinDuquesnoy/MellowPlayer/commits/develop)
[![Coverage report](https://gitlab.com/ColinDuquesnoy/MellowPlayer/badges/develop/coverage.svg)](https://gitlab.com/ColinDuquesnoy/MellowPlayer/commits/develop)
[![Release](https://img.shields.io/github/release/ColinDuquesnoy/MellowPlayer.svg)](https://github.com/ColinDuquesnoy/MellowPlayer/releases)

# About

*MellowPlayer* is a **free**, **open source** and **cross-platform** desktop application
that runs **web-based music streaming services** in its own window and
provides **integration with your desktop** (hotkeys, multimedia keys, system tray,
notifications and more).

*MellowPlayer is a Qt based alternative to* [NuvolaPlayer](https://tiliado.eu/nuvolaplayer/),
*specifically crafted for* [KaOS](http://kaosx.us/).

# Supported services:

- [Deezer](http://deezer.com)
- [Mixcloud](http://mixcloud.com)
- [Soundcloud](http://soundcloud.com)
- [Spotify](http://spotify.com)
- [TuneIn](http://tunein.com/)
- [8tracks](http://8tracks.com/)
- [Google Play Music](https://play.google.com/music/listen)


# Resources

- [Official website](https://colinduquesnoy.github.io/MellowPlayer/)
- [Documentation](http://mellowplayer.readthedocs.org/en/webengine/)

# License

MellowPlayer is licensed under the GPL license.

# Requirements

## Supported platforms

- GNU/Linux
    - KaOS
    - ArchLinux
    - Fedora >= 25
- Mac OSX
- Windows

## Dependencies

- [Qt](https://www.qt.io/) >= 5.7
- [CMake](https://cmake.org/) >= 3.5
- [Snorenotify]() >= 0.7 (Windows/OSX, optional)
- [libnotify]() (GNU/Linux only, optional)

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

Building MellowPlayer requires a **C++14** compiler:

- GCC >= 5.x
- Clang >= 3.5
- MSVC 2015 Update 2 

## GNU/Linux

```bash
mkdir build && cd build
cmake ..
make
```

## OSX

```bash
mkdir build && cd build
brew install qt5 cmake
cmake -DCMAKE_PREFIX_PATH=/usr/local/opt/qt5 ..
make
```

## Windows

```bash
mkdir build && cd build
cmake -G "Visual Studio 14 2015 Win64" -DCMAKE_BUILD_TYPE=Release .. 
cmake --build . --config Release
```

# Build options

You can specify the following options when calling cmake:

- ``-DCMAKE_BUILD_TYPE=``: **Debug** or **Release** - Default is **Debug**.
- ``-DBUILD_TESTS=``: **ON** or **OFF** - Default is **ON**.
- ``-DENABLE_COVERAGE``: **ON** or **OFF** (requires ``BUILD_TEST=ON`` and ``CMAKE_BUILD_TYPE=Debug``) - Default is **OFF** .

# Running the test suite

Make sure you've built MellowPlayer with -DBUILD_TEST.

```bash
cd build\tests
./MellowPlayer.Tests
```

# Contributing

**[Version 3.0](https://gitlab.com/ColinDuquesnoy/MellowPlayer/milestones/14) is in active development on the develop branch**

MellowPlayer is an open-source application that needs your help to go on growing and improving!

There are many ways for developer and non-developers to contribute to the project. You can report (and fix) bugs, add new translations, add support for new streaming services (the core team won't support all services, especially those which are not free), and so on...

If you feel like you want to contribute to the project, make sure to checkout the [contributing guidelines](https://github.com/ColinDuquesnoy/MellowPlayer/blob/master/CONTRIBUTING.rst)!

