Plugins
=======

Introduction
------------

MellowPlayer can be extended by writing a *streaming service integration plugin*.

*A streaming service integration plugin* is just a directoy that contains some specific files:

- **integration.js**: the actual code that integrates the service into MellowPlayer
- **logo.svg**: the logo of the service
- **metadata.ini**: plugin's metadata
- **theme.json**: optional theme definition. The colors defined in this file are used through the whole user interface if theme is set to **adaptive**.

The file **integration.js** contains a series of function that you must implement. Those functions will get called
by the C++ application for updating the player state or when the user triggered an action (play, pause,...).


MellowPlayer will look for plugins in the following directories:

- **$CURRENT_WORKING_DIR/plugins**
- **/usr/share/mellowplayer/plugins**
- **/usr/local/share/mellowplayer/plugins**
- **~/.local/share/MellowPlayer/plugins**


Create a new plugin
-------------------

**This feature does not exists anymore in v2.95.0, we will be back for v3.0.0**

To create a plugin, go to the **Control** drop down menu or the **Developer** main menu and click on **Create plugin**. 

This will bring the following wizard:

.. image:: ../_static/wizard_new_plugin_01.png
    :align: center

Fill in the details:

.. image:: ../_static/wizard_new_plugin_02.png
    :align: center


When you're done, select your new plugin service in the services dialog that will automatically pop out:

.. image:: ../_static/wizard_new_plugin_03.png
    :align: center


Functions to implement
----------------------

Here is a brief description of the functions you need to implement in order to 
integrate a new web-based streaming service.

update()
++++++++

This function is called regularly to update the player information.

You must return a dictionnary with the following keys:

- **playbackStatus** *(int)*: Use mellowplayer.PlaybackStatus)*. **Mandatory**
- **canSeek** *(bool)*: True if the player can seek into the current song.
- **canGoNext** *(bool)*: True if the player can skip to the next song.
- **canGoPrevious** *(bool)*: True if the playe can skip to the previous song.
- **canAddToFavorites** *(bool)*: True if the user can add or remove the current song from a list of favorites
- **volume** *(float [0-1])*: Player volume. Optional, leave it 1 if your plugin cannot control the volume.
- **songId** *(str)*: The unique id of the current song. **Mandatory**. Either use a GUID or hash the song title if no id is available.
- **songTitle** *(str)*: The title of the current song. **Mandatory**
- **artistName** *(str)*: The name of the artist of the current. Optional.
- **albumTitle** *(str)*: The name of the album of the current song. Optional.
- **artUrl** *(str)*: The current song art url.
- **isFavorite** *(bool)*: True if the song is in the list of the user's favorite songs. Optional.
- **duration** *(int [seconds])*: The duration of the song, in seconds. Optional (but nice).
- **position** *(int [seconds])*: The position (or elapsed time) of the song, in seconds. Optional (but nice).

play()
++++++

Starts playback.

pause()
+++++++

Pauses playback.

goNext()
++++++++

Skips to next song.

goPrevious()
++++++++++++

Skips to previous song.

setVolume(volume)
+++++++++++++++++

Sets the player's volume.
  
**volume** is a *float* in the range [0-1].

addToFavorites()
++++++++++++++++

Adds song to favorites.

removeFromFavorites()
+++++++++++++++++++++

Removes song from favorites.

seekToPosition(position)
++++++++++++++++++++++++

Seeks to the specified position. 

**position** is an *int* representing the new position inside the song (in seconds).


PlaybackStatus
--------------

MellowPlayer will inject a few constants that you can use for representing the current PlaybackStatus:

- **mellowplayer.PlaybackStatus.STOPPED**: indicates that the playback has stopped.
- **mellowplayer.PlaybackStatus.PAUSED**: indicates that the playback has paused.
- **mellowplayer.PlaybackStatus.BUFFERING**: indicates that the a song is buffering.
- **mellowplayer.PlaybackStatus.PLAYING**: indicates that the a song is currently playing.
