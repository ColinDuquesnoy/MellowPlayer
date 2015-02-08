## 1.1.0

### New features

- new notification systems: use KNotification on KDE Sc/Plasma 5 and notify-send on other
  linux desktop environments. Now we are able to show the track art in the notification popup.
- add a preference widget for the new notification system: you can fine tune the notification you
  would like to see or hide.
- show the name of the music streaming service in the window title bar
- add some command line arguments (e.g. to start with a predefined service or to enable the web inspector).
- add Travis CI integration (test compilation process + a few functional tests, still no test suite)
- add a Wiki action to the main window: triggering this action will open a browser to our wiki.

### Fixed bugs

- fix a couple of bugs related to buffering state in various streaming service. Those bugs were not 
  visible with the old notification system
- improve mpris interface on other desktops (mainly gnome shell)
- improve french translation

## 1.0.0

### New features
- add support for Grooveshark Mobile
- add support for Mixcloud
- implement "Add to favorite"
- flash plugin detection + warning if you attempt to use a service that require flash but flash cannot be found

### Fixed bugs
- polish mpris interface (buttons are now disabled/enabled depending on the context)

## 1.0.0-beta

First public release
