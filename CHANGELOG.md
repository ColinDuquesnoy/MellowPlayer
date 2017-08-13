# Change Log

## [2.99.0](https://github.com/ColinDuquesnoy/MellowPlayer/tree/2.99.0) (2017-08-06)
[Full Changelog](https://github.com/ColinDuquesnoy/MellowPlayer/compare/2.95.0...2.99.0)

**Implemented enhancements:**

- Check audio codecs support [\#82](https://github.com/ColinDuquesnoy/MellowPlayer/issues/82)
- Command-Line flags to toggle/get song favorite status [\#77](https://github.com/ColinDuquesnoy/MellowPlayer/issues/77)
- Add copy and paste for the context menu [\#73](https://github.com/ColinDuquesnoy/MellowPlayer/issues/73)
- Add a menu entry to report issue on github [\#65](https://github.com/ColinDuquesnoy/MellowPlayer/issues/65)
- Limit ListeningHistory [\#64](https://github.com/ColinDuquesnoy/MellowPlayer/issues/64)
- Add Tidal support [\#59](https://github.com/ColinDuquesnoy/MellowPlayer/issues/59)
- Add youtube support [\#58](https://github.com/ColinDuquesnoy/MellowPlayer/issues/58)
- ListeningHistory: smarter song tracking [\#55](https://github.com/ColinDuquesnoy/MellowPlayer/issues/55)
- Call cache cleaner when closing MellowPlayer [\#54](https://github.com/ColinDuquesnoy/MellowPlayer/issues/54)
- Add global menu on OSX [\#53](https://github.com/ColinDuquesnoy/MellowPlayer/issues/53)
- Internationalisation [\#52](https://github.com/ColinDuquesnoy/MellowPlayer/issues/52)
- Add ability to disable a service [\#51](https://github.com/ColinDuquesnoy/MellowPlayer/issues/51)
- Add hotkey to restore window [\#50](https://github.com/ColinDuquesnoy/MellowPlayer/issues/50)
- Add theme setting [\#49](https://github.com/ColinDuquesnoy/MellowPlayer/issues/49)
- Check for update mechanism [\#48](https://github.com/ColinDuquesnoy/MellowPlayer/issues/48)
- Add command line options [\#43](https://github.com/ColinDuquesnoy/MellowPlayer/issues/43)
- Allow to reorder services via drag & drop [\#42](https://github.com/ColinDuquesnoy/MellowPlayer/issues/42)
- Plugin wizard [\#38](https://github.com/ColinDuquesnoy/MellowPlayer/issues/38)

**Fixed bugs:**

- Youtube fullscreen does not work [\#87](https://github.com/ColinDuquesnoy/MellowPlayer/issues/87)
- High DPI issue [\#71](https://github.com/ColinDuquesnoy/MellowPlayer/issues/71)
- Soundcloud integration broken [\#60](https://github.com/ColinDuquesnoy/MellowPlayer/issues/60)

**Merged pull requests:**

- German translation finished. [\#89](https://github.com/ColinDuquesnoy/MellowPlayer/pull/89) ([ZeroDot1](https://github.com/ZeroDot1))

## [2.95.0](https://github.com/ColinDuquesnoy/MellowPlayer/tree/2.95.0) (2017-06-24)
[Full Changelog](https://github.com/ColinDuquesnoy/MellowPlayer/compare/2.2.5...2.95.0)

**Implemented enhancements:**

- Ported to QML + Material Design theme
- Adaptive theme that follows the theme of the currently running streaming service
- Fast switching between running services (Ctrl+Tab/Ctrl+Shift+Tab)
- Optional listening history, disabled by default
- Added a button to quickly turn off/on notifications
- Added support for self hosted services

### 2.2.5

- Fix broken soundcloud integration plugin

### 2.2.4

- Fix broken spotify integration plugin (due to redirection to open.spotify.com).

**Note**
that Widevine plugin is needed to use spotify.

### 2.2.3

- Fix broken mixcloud integration plugin
- Fix broken google play music integration plugin

### 2.2.2

- Fix broken 8tracks integration
- Fix missing art url in soundcloud
- Improve single application controller on linux; now handle crash or premature termination of the unique app instance.
- Internal refactoring: use QCommandLineParser instead of our own

### 2.2.1

- Fix segfault on application exit if lyrics pane is visible.

### 2.2.0

- Add a lyrics panel that show the lyrics of the current song (using the chartlyrics web service).

## 2.1

### 2.1.2

- Small UI tweaks for Windows 10 (set toolbar background color to white)

### 2.1.1

- Fix version number not updated in previous release

### 2.1.0

- Add support for Google Play Music

## 2.0

### 2.0.1

**Fixed bugs**

- [Mixcloud] Fix missing album arts due to change in URL.
- [All] Fix album arts cache grows indefinitely. Now the cache will get cleaned on application startup.
- [Windows] Fix empty list of plugins if user pinned the app to the panel when the app was running.

### 2.0.0

**Fixed bugs**

- [TuneIn] Fix missing radio art if broadcast.Guide is the same as a previous broadcast

### 2.0.0 Release Candidate (v1.99)

- Add TuneIn integration plugin
- Fix missing vcredist for the windows installer.

### 2.0 beta (v1.95)

**General:**

- Ported to **QtWebEngine**
- 2 new services: **Spotify** and **8tracks**
- Web streaming services **plugins are now written in pure javascript** (a
wizard will guide you through the steps of creating a new plugin)
- **New** design for the **home page**
- **Update notifier**
- Translations are now managed on **transifex**: https://www.transifex.com/colinduquesnoy/mellowplayer/


**GNU/Linux:**

- Build is now cross desktop (no more desktop specific release)
- Add ability to turn a streaming service into a standalone app

## 1.5

### 1.5.2

- Remove Rdio service (service has shutdown).

### 1.5.1

- [Deezer] Fix missing album art in notifications and MPRIS2 interface
- [Mixcloud] Improve integration:

- Add ability to skip to previous/next song
- Add ability to retrieve song duration and song position
- Add ability to seek into the current mixcloud (this is a bit slow in webkit, works much better in qtwebengine).

### 1.5.0

**UI Improvements:**

- Improvements to the toolbar on linux and windows
- Add web page navigation actions (back, forward, reload, home)
- Add ability to hide both the menu and the toolbar
- Add ability to run the application in fullscreen
- Use a svg icon for the desktop entry on GNU/Linux. Icon will be installed into
``/usr/share/icons/hicolor/scalable/apps`` instead of ``/usr/share/pixmaps``

## 1.4

### 1.4.0

**New features:**

- Remove grooveshark plugins since the service has shutdown
- Add [Rdio](http://rdio.com) integration (HTML5 service, free with audio ads)
- UI improvements: remove the confusing stop action from the menus (all the supported services
don't have a stop action, just pause).
- OSX improvements:
- Add a dock menu with play/pause, next, previous and add to favorites action
- Use the same behaviour as on Ubuntu: no minimize to tray (tray is used just for messages), quit/close exits the
  application
- Make flash an optional runtime dependency: flash plugins won't get enabled (even if installed) except
for the service that require it (Deezer, Mixcloud and Soundcloud)
- Get rid of Qt4 build support, now MellowPlayer is Qt5 only (even on Windows)

**Fixed bugs:**

- Fix a corner case where the wrong image was used for the "song changed" notification (linux only,
all desktop environments affected)
- Fix/workaround key repeat issue with KGlobalAccel (KDE Sc/Plasma 5 only)
- Fix "Close" action on minimized windows (all platforms except OSX and Ubuntu/Unity)
- Fix "Add to favorites" action on Windows
- Fix frozen player issue introduced in v1.3


## 1.3

### 1.3.0

**New features:**

- Add support Ubuntu/Unity (available through ppa:colin-duquesnoy/stable)
- Disable tray icon
- Fix double global menu
- Add support for unity quicklists
- Add support for Gnome Settings Daemon (multimedia keys)
- Project stucture cleanup (all code has been moved into the src folder)
- Use Restore Window actiont to show the current service name and the song info
(or the service status, e.g. Loading or Stopped)

**Fixed bugs:**

- Select service dialog: don't reload page if service has not changed but user
choose OK.
- Prevent the "Stopped" notification from being shown when switching service
- Use restoreWindow instead of show to make sure the main window is active
before showing any preference dialog.


## 1.2

### 1.2.1

**New features:**

- Soundcloud song art can now be used for notifications and mpris2 interface on Linux.

**Fixed bugs:**

- Fix broken soundcloud integration (due to a change to the soundcloud player interface).

### 1.2.0

**New features**

- Soundcloud integration
- New streaming service icons

**Fixed bugs**

- Fix cookies management: use one cookie jar per service (#3)
- Fix grooveshark retro images not appearing in kmediaplayer

## 1.1

### 1.1.1

Use grooveshark retro instead of the new grooveshark website.
The new website does not work well with QtWebkit (freeze on large collection, completely unusable).
We will reintroduce the official grooveshark as soon as QtWebEngine starts supporting flash.

### 1.1.0

**New features**

- New notification systems: use KNotification on KDE Sc/Plasma 5 and notify-send on other
linux desktop environments. Now we are able to show the track art in the notification popup.
- Add a preference widget for the new notification system: you can fine tune the notification you
would like to see or hide.
- Show the name of the music streaming service in the window title bar
- Add some command line arguments (e.g. to start with a predefined service or to enable the web inspector).
- Add Travis CI integration (test compilation process + a few functional tests, still no test suite)
- Add a Wiki action to the main window: triggering this action will open a browser to our wiki.

**Fixed bugs**

- Fix a bug which prevented the os from shutting down (logout/shutdown/restart) if the window was visible
- Fix a couple of bugs related to buffering state in various streaming service. Those bugs were not
visible with the old notification system
- Improve mpris interface on other desktops (mainly gnome shell)
- Improve french translation

## 1.0

### 1.0.0

**New features**

- Add support for Grooveshark Mobile
- Add support for Mixcloud
- Implement "Add to favorite"
- Flash plugin detection + warning if you attempt to use a service that require flash but flash cannot be found

**Fixed bugs**

- Polish mpris interface (buttons are now disabled/enabled depending on the context)

### 1.0.0-beta

- First public release


\* *This Change Log was automatically generated by [github_changelog_generator](https://github.com/skywinder/Github-Changelog-Generator)*