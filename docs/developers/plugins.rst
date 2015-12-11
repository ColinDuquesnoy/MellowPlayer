Plugins
=======

Introduction
------------

MellowPlayer can be extended by writing a *streaming service integration plugin*.

*A streaming service integration plugin* is just a directoy that contains some specific files:

- **description.html**: describes the web streaming service. This description
  appear in the service selector dialog.
- **integration.js**: the actual code that integrates the service into MellowPlayer
- **logo.svg**: the logo of the service
- **metadata.ini**: plugin's metadata

The file **integration.js** contains a series of function that you must implement. Those functions will get called
by the C++ application for updating the player state or when the user triggered an action (play, pause,...).


MellowPlayer will look for plugins in the following directories:

- **$CURRENT_WORKING_DIR/plugins**
- **/usr/share/mellowplayer/plugins**
- **/usr/local/share/mellowplayer/plugins**
- **~/.local/share/mellowplayer/plugins**


You will find a plugin template in **utils/templates**. Just copy the ``plugin`` template directory 
to one of the above locations, rename it to the name of the service you want to add and start 
editing the 4 documents aforementioned.

Functions to implement
----------------------

Here is a brief description of the functions you need to implement in order to 
integrate a new web-based streaming service.

updatePlayerInfo()
++++++++++++++++++

This function is called regularly to update the player information.

You must return a dictionnary with the following keys:

- **PlaybackStatus** *(int, use mellowplayer.PlaybackStatus)*
- **CanSeek** *(bool)*
- **CanGoNext** *(bool)*
- **CanGoPrevious** *(bool)*
- **CanAddToFavorites** *(bool)*
- **Volume** *(float [0-1])*

updateSongInfo()
++++++++++++++++

This function is called regularly to update the song information.

You must return a dictionnary with the following keys:

- **SongId** *(str)*
- **SongTitle** *(str)*
- **ArtistName** *(str)*
- **AlbumTitle** *(str)*
- **ArtUrl** *(str)*
- **Favorite** *(bool)*
- **Duration** *(int [seconds])*
- **Position** *(int [seconds])*

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

addToFavorites(add)
+++++++++++++++++++

Adds/Removes song from favorites.

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
