Getting started
===============

First startup
-------------

On the first startup, you'll be presented with the following screen:

.. image:: ../_static/home-page.png
    :align: center

Just click on a service to start running it. You can start multiple service at the same time and quickly switch between
them using Ctrl+Tab/Ctrl+Shift+Tab.

.. image:: ../_static/main-window.png
    :align: center

You can get back to the service selection page using F8 or the select service button:

.. image:: ../_static/select-services-button.png
    :align: center

Application Settings
--------------------

You can change application settings by clicking on the menu button and by selecting the Settings entry or by pressing F2:

.. image:: ../_static/settings-menu.png
    :align: center

This will bring the following page:

.. image:: ../_static/general-settings.png
    :align: center

There are a series of settings category:

- General: general options
- Appearance: let you change the appearance of the application
- Notifications: let you change some notification settings
- Shortcuts: let you change all the application shortcuts
- Privacy: enable or disable privacy related options
- Services: list the available services and let you change their default url.
- Cache: a few buttons that let you clear the application cache (album art covers,...) and clear the web cookies.


Notifications
-------------

By default, MellowPlayer will display a notification whenever the current track changed.


.. image:: ../_static/notification-plasma5.png
    :align: center


You can change the notifications behaviour in the application settings page

.. image:: ../_static/notification-settings.png
    :align: center

and you can also quickly toggle notifications on/off using the button in the toolbar:

.. image:: ../_static/notification-button.png
    :align: center

Listening History
-----------------

MellowPlayer can keep track of your listens and display it in a side panel. This feature is OFF by default.

You can see your listening history by pressing the listening history button:

.. image:: ../_static/listening-history-button.png
    :align: center

Here is what the history look like:

.. image:: ../_static/listening-history.png
    :align: center

You can search the history and filter by service by clicking on the search icon

.. image:: ../_static/listening-history-search.png
    :align: center

MPRIS2 Interface
----------------

Most GNU/Linux Desktop Environments have a MPRIS client interface that sits
in the system tray and let you control media players easily.

MellowPlayer implements the DBUS MPRIS 2 interface and should appear in your MPRIS2
client interface:

- Plasma 5:

.. image:: ../_static/mpris-player-plasma.png
    :align: center

- Gnome:

.. image:: ../_static/mpris-player-gnome.png
    :align: center

- Unity:

.. image:: ../_static/mpris-player-unity.png
    :align: center
