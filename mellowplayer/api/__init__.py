"""
This package contains the application public API (for writing
plugins):
  - plugins api: the various plugins types (base classes)
  - song api: Song, SongInfo, SongStatus,...
  - player api: contains the player object that is used to control the
                current integration service.
  - utility api: FileDownloader
"""
from mellowplayer.utils import FileDownloader
from .song import SongStatus, Song


# Public API
__all__ = [
    'FileDownloader',
    'Song',
    'SongStatus'
]
