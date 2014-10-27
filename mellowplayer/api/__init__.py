"""
This package contains the application API:
  - Service API: an API for integrating new services
  - common classes: Song, SongInfo, SongStatus,...

"""
from .song import SongStatus, Song
from .service import ServiceIntegration


# Public API
__all__ = [
    'ServiceIntegration',
    'Song',
    'SongStatus'
]
