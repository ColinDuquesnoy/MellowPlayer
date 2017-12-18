Features
========

- Cross-platform (available on Windows, Mac OSX and GNU/Linux)
- System tray integration and notifications
- Mpris2 support (GNU/Linux only)
- Hotkeys and media player keys support
- Plugin based application (you can add support for a new web-based music
  streaming service by writing a **javascript plugin**)
- User scripts support

Supported Services
------------------


+------------------------+---+---+---+---+------------+----------+-----+
| Service                | G | A | W | O | Require    | Require  | Req |
|                        | N | p | i | S | non-free   | flash    | uir |
|                        | U | p | n | x | HTML       |          | e   |
|                        | / | I | d |   | codecs     |          | drm |
|                        | L | m | o |   |            |          |     |
|                        | i | a | w |   |            |          |     |
|                        | n | g | s |   |            |          |     |
|                        | u | e |   |   |            |          |     |
|                        | x |   |   |   |            |          |     |
+========================+===+===+===+===+============+==========+=====+
| `Deezer`_              | Y | Y | Y | Y | Yes (or    | Yes (or  | No  |
|                        | e | e | e | e | flash)     | non-free |     |
|                        | s | s | s | s |            | codecs)  |     |
+------------------------+---+---+---+---+------------+----------+-----+
| `Mixcloud`_            | Y | N | N | N | Yes        | No       | No  |
|                        | e | o | o | o |            |          |     |
|                        | s |   |   |   |            |          |     |
+------------------------+---+---+---+---+------------+----------+-----+
| `Soundcloud`_          | Y | N | N | N | Yes        | No       | No  |
|                        | e | o | o | o |            |          |     |
|                        | s |   |   |   |            |          |     |
+------------------------+---+---+---+---+------------+----------+-----+
| `Spotify`_             | Y | N | N | N | Yes        | No       | Yes |
|                        | e | o | o | o |            |          |     |
|                        | s |   |   |   |            |          |     |
+------------------------+---+---+---+---+------------+----------+-----+
| `TuneIn`_              | Y | Y | Y | Y | Depends on | No       | No  |
|                        | e | e | e | e | the stream |          |     |
|                        | s | s | s | s |            |          |     |
+------------------------+---+---+---+---+------------+----------+-----+
| `8tracks`_             | Y | Y | Y | Y | Depends on | No       | No  |
|                        | e | e | e | e | the stream |          |     |
|                        | s | s | s | s |            |          |     |
+------------------------+---+---+---+---+------------+----------+-----+
| `Google Play Music`_   | Y | Y | Y | Y | ?          | ?        | ?   |
|                        | e | e | e | e |            |          |     |
|                        | s | s | s | s |            |          |     |
+------------------------+---+---+---+---+------------+----------+-----+
| `Youtube`_             | Y | Y | Y | Y | Depends on | No       | No  |
|                        | e | e | e | e | the stream |          |     |
|                        | s | s | s | s |            |          |     |
+------------------------+---+---+---+---+------------+----------+-----+
| `Tidal`_               | Y | Y | Y | Y | No         | Yes      | No  |
|                        | e | e | e | e |            |          |     |
|                        | s | s | s | s |            |          |     |
+------------------------+---+---+---+---+------------+----------+-----+
| `Anghami`_             | Y | N | N | N | Yes        | No       | No  |
|                        | e | o | o | o |            |          |     |
|                        | s |   |   |   |            |          |     |
+------------------------+---+---+---+---+------------+----------+-----+
| `Pocket Casts`_        | Y | N | N | N | Yes        | No       | No  |
|                        | e | o | o | o |            |          |     |
|                        | s |   |   |   |            |          |     |
+------------------------+---+---+---+---+------------+----------+-----+
| `HearThisAt`_          | Y | Y | Y | Y | Depends on | No       | No  |
|                        | e | e | e | e | the stream |          |     |
|                        | s | s | s | s |            |          |     |
+------------------------+---+---+---+---+------------+----------+-----+
| `Jamendo`_             | Y | Y | Y | Y | No         | No       | No  |
|                        | e | e | e | e |            |          |     |
|                        | s | s | s | s |            |          |     |
+------------------------+---+---+---+---+------------+----------+-----+
| `Radionomy`_           | Y | Y | Y | Y | Depends on | No       | No  |
|                        | e | e | e | e | the stream |          |     |
|                        | s | s | s | s |            |          |     |
+------------------------+---+---+---+---+------------+----------+-----+
| `Wynk`_                | Y | N | N | N | Yes        | No       | No  |
|                        | e | o | o | o |            |          |     |
|                        | s |   |   |   |            |          |     |
+------------------------+---+---+---+---+------------+----------+-----+
| `ympd`_                |
+------------------------+---+---+---+---+------------+----------+-----+

.. _Deezer: http://deezer.com
.. _Mixcloud: http://mixcloud.com
.. _Soundcloud: http://soundcloud.com
.. _Spotify: http://spotify.com
.. _TuneIn: http://tunein.com/
.. _8tracks: http://8tracks.com/
.. _Google Play Music: https://play.google.com/music/listen
.. _Youtube: https://youtube.com/
.. _Tidal: https://listen.tidal.com/
.. _Anghami: https://www.anghami.com/
.. _Pocket Casts: https://play.pocketcasts.com/
.. _HearThisAt: https://hearthis.at/
.. _Jamendo: https://www.jamendo.com/start
.. _Radionomy: https://www.radionomy.com/
.. _Wynk: https://www.wynk.in/music
.. _ympd: https://github.com/notandy/ympd

User Scripts
------------

With MellowPlayer >= 3.1 you have the possibility to use user scripts.

This means that you can customize the look and feel of a streaming service as you like it, or simply to add features you miss.

    - `Download and use different themes`_
    - `Download and use different user scripts`_

.. _Deezer: http://deezer.com
.. _Mixcloud: http://mixcloud.com
.. _Soundcloud: http://soundcloud.com
.. _Spotify: http://spotify.com
.. _TuneIn: http://tunein.com/
.. _8tracks: http://8tracks.com/
.. _Google Play Music: https://play.google.com/music/listen
.. _Youtube: https://youtube.com/
.. _Tidal: https://listen.tidal.com/
.. _Anghami: https://www.anghami.com/
.. _Pocket Casts: https://play.pocketcasts.com/
.. _HearThisAt: https://hearthis.at/
.. _Jamendo: https://www.jamendo.com/start
.. _Radionomy: https://www.radionomy.com/
.. _Wynk: https://www.wynk.in/music
.. _ympd: https://github.com/notandy/ympd

.. _Download and use different themes: https://userstyles.org/
.. _Download and use different user scripts: https://greasyfork.org/en/