from mellowplayer.qt import QtDBus
if QtDBus:
    from .mpris2 import Mpris2
else:
    class Mpris2:
        def __init__(self, *args):
            pass

        def setParent(self, *args):
            pass

        def destroy(self):
            pass

from .player import Player
from .service import ServiceManager


__all__ = [
    'Mpris2',
    'Player',
    'ServiceManager'
]
