## 2.2

### 2.2.3

- Fix broken mixcloud integration plugin
- Fix broken google play music integration plugin

### 2.2.2

- Fix broken 8tracks integration
- Fix missing art url in soundcloud
- Improve single application controller on linux; now handle crash or premature termination of the unique app instance.
- Internal refactoring: use QCommandLineParser instead of our own

### 2.2.1

Fix segfault on application exit if lyrics pane is visible.

### 2.2.0

Add a lyrics panel that show the lyrics of the current song (using the chartlyrics web service).

## 2.1

### 2.1.2

Small UI tweaks for Windows 10 (set toolbar background color to white)

### 2.1.1

Fix version number not updated in previous release

### 2.1.0

Add support for Google Play Music

## 2.0

### 2.0.1

**Fixed bugs**

- [Mixcloud] fix missing album arts due to change in URL.
- [All] fix album arts cache grows indefinitely. Now the cache will get cleaned on application startup.
- [Windows] fix empty list of plugins if user pinned the app to the panel when the app was running.

### 2.0.0

**Fixed bugs**

- [TuneIn] fix missing radio art if broadcast.Guide is the same as a previous broadcast

### 2.0.0 Release Candidate (v1.99)

- add TuneIn integration plugin
- fix missing vcredist for the windows installer.

### 2.0 beta (v1.95)

**General:**

- ported to **QtWebEngine**
- 2 new services: **Spotify** and **8tracks**
- web streaming services **plugins are now written in pure javascript** (a
    wizard will guide you through the steps of creating a new plugin)
- **new** design for the **home page**
- **update notifier**
- translations are now managed on **transifex**: https://www.transifex.com/colinduquesnoy/mellowplayer/


**GNU/Linux:**

    - build is now cross desktop (no more desktop specific release)
    - add ability to turn a streaming service into a standalone app

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

- improvements to the toolbar on linux and windows
- add web page navigation actions (back, forward, reload, home)
- add ability to hide both the menu and the toolbar
- add ability to run the application in fullscreen
- use a svg icon for the desktop entry on GNU/Linux. Icon will be installed into
  ``/usr/share/icons/hicolor/scalable/apps`` instead of ``/usr/share/pixmaps``

## 1.4

### 1.4.0

**New features:**

- Remove grooveshark plugins since the service has shutdown
- Add [Rdio](http://rdio.com) integration (HTML5 service, free with audio ads)
- UI improvements: remove the confusing stop action from the menus (all the supported services
  don't have a stop action, just pause).
- OSX improvements:
    - add a dock menu with play/pause, next, previous and add to favorites action
    - use the same behaviour as on Ubuntu: no minimize to tray (tray is used just for messages), quit/close exits the
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
    - disable tray icon
    - fix double global menu
    - add support for unity quicklists
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

- soundcloud song art can now be used for notifications and mpris2 interface on Linux.

**Fixed bugs:**

- fix broken soundcloud integration (due to a change to the soundcloud player interface).

### 1.2.0

**New features**

- Soundcloud integration
- New streaming service icons

**Fixed bugs**

- fix cookies management: use one cookie jar per service (#3)
- fix grooveshark retro images not appearing in kmediaplayer

## 1.1

### 1.1.1

Use grooveshark retro instead of the new grooveshark website.
The new website does not work well with QtWebkit (freeze on large collection, completely unusable).
We will reintroduce the official grooveshark as soon as QtWebEngine starts supporting flash.

### 1.1.0

**New features**

- new notification systems: use KNotification on KDE Sc/Plasma 5 and notify-send on other
  linux desktop environments. Now we are able to show the track art in the notification popup.
- add a preference widget for the new notification system: you can fine tune the notification you
  would like to see or hide.
- show the name of the music streaming service in the window title bar
- add some command line arguments (e.g. to start with a predefined service or to enable the web inspector).
- add Travis CI integration (test compilation process + a few functional tests, still no test suite)
- add a Wiki action to the main window: triggering this action will open a browser to our wiki.

**Fixed bugs**

- fix a bug which prevented the os from shutting down (logout/shutdown/restart) if the window was visible
- fix a couple of bugs related to buffering state in various streaming service. Those bugs were not
  visible with the old notification system
- improve mpris interface on other desktops (mainly gnome shell)
- improve french translation

## 1.0

### 1.0.0

**New features**

- add support for Grooveshark Mobile
- add support for Mixcloud
- implement "Add to favorite"
- flash plugin detection + warning if you attempt to use a service that require flash but flash cannot be found

**Fixed bugs**

- polish mpris interface (buttons are now disabled/enabled depending on the context)

### 1.0.0-beta

First public release
