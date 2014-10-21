"""
This package contains the application API:
  - Service API: an API for integrating new services
  - common classes: Song, SongInfo, SongStatus,...

"""
from .service import ServiceIntegration
from .service import ServicePlugin
from .service import ServiceManager


# Public API
__all__ = [
    'ServiceIntegration',
    'ServicePlugin',
    'ServiceManager'
]
