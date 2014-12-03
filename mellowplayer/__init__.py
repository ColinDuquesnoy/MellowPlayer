"""
**MellowPlayer** is a free and cross-platform desktop application that runs a
web interface of **cloud music services** in its own window and provides
**integration with your desktop** (multimedia keys, system tray,
notifications and more).

"""
__version__ = '1.0a1'
_api_initialized = False


def setup_sip_api():
    global _api_initialized

    if not _api_initialized:
        _api_initialized = True
