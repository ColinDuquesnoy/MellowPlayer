MellowPlayer Library - API reference
=====================================

MellowPlayer exposes it's core functionnality to the plugins through this library.

This page covers the public API reference of this library.

There is a convenience header that you can include to get acces to the whole API: **mellowplayer.h**


Plugin Interfaces
-----------------

This section describe the interfaces that must be implemented to create a 
new plugin. You can either **create cloud music service plugin** or a **generic extension**.


.. doxygenclass:: ICloudMusicService
    :members:
    
.. doxygenclass:: IExtension
    :members:

Plugins metadata
----------------

This section describes the plugin metadata, common to both types of plugins.

Those metadata are read from the json description that you specify when you declare
the plugin interface.

.. doxygenstruct:: PluginMetaData
    :members:

Services
--------

The application exposes a series of **services** that you can retrieve from
anywhere using the following static class:

.. doxygenclass:: Services
    :members:

Cloud Player API
----------------

This section describes the player API that you can use from your plugin to interact 
with the cloud media player.
    
.. doxygenclass:: PlayerInterface
    :members:
    
.. doxygenstruct:: SongInfo
    :members:
    
.. doxygenenum:: PlaybackStatus


Plugins Managers API
--------------------

This section describes the plugins manager and actual plugin classes.
    
.. doxygenclass:: CloudServicesManager
    :members:
    
.. doxygenclass:: ExtensionsManager
    :members:

.. doxygenclass:: CloudServicePlugin
    :members:

.. doxygenclass:: ExtensionPlugin
    :members:


Utility
-----------

This section describes the available utility classes/functions.
    
.. doxygenclass:: UrlDownloader
    :members:
    
.. doxygenfunction:: playbackStatusToString



