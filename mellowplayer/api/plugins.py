"""
This module contains the various plugins types (base classes).
"""
from mellowplayer.qt import to_pyobject
from yapsy.IPlugin import IPlugin


class IServiceIntegrationPlugin(IPlugin):
    """
    Base class for service integration plugins.

    Such plugins provide an interface to a specific cloud music service
    by interacting with the current web page (
    see :func:`ServiceIntegrationPlugin.jseval`) .

    A service integration plugin must implement the following methods:
        - :func:`ServiceIntegrationPlugin.play`
        - :func:`ServiceIntegrationPlugin.pause`
        - :func:`ServiceIntegrationPlugin.stop`
        - :func:`ServiceIntegrationPlugin.current_song`

    and define the following class attributes:

        - :attr:`ServiceIntegrationPlugin.url`
        - :attr:`ServiceIntegrationPlugin.maintainer_name`
        - :attr:`ServiceIntegrationPlugin.maintainer_link`
        - :attr:`ServiceIntegrationPlugin.version`
        - :attr:`ServiceIntegrationPlugin.version_minor`
        - :attr:`ServiceIntegrationPlugin.icon`
        - :attr:`ServiceIntegrationPlugin.description`

    """
    #: Service URL (e.g. http://grooveshark.com/)
    url = ''
    icon = ''
    description = ''

    def play(self):
        """ Plays the current song. """
        pass

    def pause(self):
        """ Pauses the current song """
        pass

    def stop(self):
        """ Stops the current song """
        pass

    def current_song(self):
        """
        Returns the current song.

        :return: current song
        :rtype: mellowplayer.api.Song
        """
        pass

    def jseval(self, script):
        """
        Run a javascript ``script`` on the main page, see
        `QWebFrame.evaluateJavaScript`_

        :param script: Script to execute (must written in Javascript).
        :return: The results of the evaluation.

        .. _QWebFrame.evaluateJavaScript:
            http://qt-project.org/doc/qt-4.8/qwebframe.html#evaluateJavaScript
        """
        data = to_pyobject(self.web_view.page().mainFrame().evaluateJavaScript(
            script))
        return data


class IExtensionPlugin(IPlugin):
    """
    Generic extension plugin.

    Those plugins got initialized with the application object. Using the application
    object, you can do nearly anything you want, you can access the main window and
    add a menu, you can manipulate the current player/service,....

    To create an extension, just inherit from this class and implement:

        - setup
        - teardown
    """

    def setup(self, app):
        """
        Sets the plugin up.

        :param app: mellowplayer.app.Application
        """
        pass

    def teardown(self):
        """
        Tears the plugin down.
        """
        pass
