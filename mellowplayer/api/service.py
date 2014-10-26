"""
This module contains the cloud music service API.
"""
import configparser
import importlib.machinery
import logging
import os
from PyQt4 import QtCore
from mellowplayer import system
from mellowplayer.settings import Settings


class ServiceIntegration(QtCore.QObject):
    """
    Base abstract class for cloud music service integration.
    """
    #: url of the cloud service
    url = 'url of the cloud service'
    #: name of the service that will appear on the service's button on
    #: the services page.
    name = ''
    #: icon that will appear on the service's button on the services page.
    icon = ''
    #: service version (so that users may know if their favorite service
    #: has been upated when a new release is available)
    version = ''
    #: service description (rich text API)
    description = ''

    def __init__(self, webview):
        #: reference to the main web view
        self._web_view = webview

    def play(self):
        """
        Plays the current song.
        """
        raise NotImplementedError()

    def pause(self):
        """
        Pauses the current song
        """
        raise NotImplementedError()

    def stop(self):
        """
        Stops the current song
        """
        raise NotImplementedError()

    def current_song(self):
        """
        Returns the current song.

        :return: current song
        :rtype: mellowplayer.api.Song
        """
        raise NotImplementedError

    def jseval(self, script):
        """
        Run a javascript ``script`` on the main page, see
        `QWebFrame.evaluateJavaScript`_

        :param script: Script to execute (must written in Javascript).
        :return: The results of the evaluation.

        .. _QWebFrame.evaluateJavaScript:
            http://qt-project.org/doc/qt-4.8/qwebframe.html#evaluateJavaScript
        """
        return self._web_view.page().mainFrame().evaluateJavaScript(script)


class PluginMetadata:
    SECTION = 'PluginMetadata'
    def __init__(self, path):
        _logger().debug('loading plugin metadata')
        config = configparser.RawConfigParser()
        config.read(path)
        self.name = config.get(self.SECTION, 'name')
        self.url = config.get(self.SECTION, 'url')
        self.maintainer_name = config.get(self.SECTION, 'maintainer_name')
        self.maintainer_link = config.get(self.SECTION, 'maintainer_link')
        self.version = config.get(self.SECTION, 'version')
        self.version_minor = config.get(self.SECTION, 'version_minor')
        self.version_str = '%s.%s' % (self.version, self.version_minor)
        try:
            self.icon = config.get(self.SECTION, 'icon')
            if not os.path.exists(self.icon):
                pdir = os.path.abspath(os.path.join(path, os.pardir))
                self.icon = os.path.join(pdir, self.icon)
                if not os.path.exists(self.icon):
                    self.icon = None
        except configparser.ConfigParser:
            # not required
            self.icon = ''


class ServicePlugin:
    """
    A service plugin is a directory in the plugin search path that is
    made up of at least 3 files:
    - metadata.conf: describes the service plugin's metadata.
    - description.html: a long description of the service
    - integration.py: the actual service integration implentation

    .. note:: The system is heavily inspired by the nuvolaplayer's integration
              service API, with the exception that the integration plugin is
              written in Python instead of JavaScript.
    """
    FN_DESCRIPTION = 'description.html'
    FN_INTEGRATION = 'integration.py'
    FN_METADATA = 'metadata.conf'

    def __init__(self, plugin_dir, webview):
        self.integration = None
        self.metadata = None
        self.description = ''
        self._load(plugin_dir, webview)

    @classmethod
    def get_description_path(cls, plugin_dir):
        return os.path.join(plugin_dir, cls.FN_DESCRIPTION)

    @classmethod
    def get_integration_path(cls, plugin_dir):
        return os.path.join(plugin_dir, cls.FN_INTEGRATION)

    @classmethod
    def get_metadata_path(self, plugin_dir):
        return os.path.join(plugin_dir, self.FN_METADATA)

    @classmethod
    def get_required_files(cls, plugin_dir):
        paths = [
            cls.get_metadata_path(plugin_dir),
            cls.get_description_path(plugin_dir),
            cls.get_integration_path(plugin_dir)
        ]
        return paths

    @classmethod
    def check_required_files(cls, plugin_dir):
        missing_paths = []
        for pth in cls.get_required_files(plugin_dir):
            if not os.path.exists(pth):
                missing_paths.append(pth)
        return missing_paths

    def _load_description(self, plugin_dir):
        _logger().debug('loading plugin description')
        with open(self.get_description_path(plugin_dir), 'r') as f:
            self.description = f.read()

    def _load_integration(self, plugin_dir, webview):
        module = self.get_integration_path(plugin_dir)
        name = '%s_%s' % (
            os.path.split(module)[1].replace('.py', ''),
            self.metadata.name.lower())
        _logger().debug("importing <module '%s' from '%s'>", name, module)
        loader = importlib.machinery.SourceFileLoader(name, module)
        plugin_module = loader.load_module()
        classname = '%sServiceIntegration' % self.metadata.name
        _logger().debug('loading %s.%s', name, classname)
        loaded_class = getattr(plugin_module, classname)
        self.integration = loaded_class(webview)

    def _load(self, plugin_dir, webview):
        """
        Loads a plugin from the 3 required files (metadata, description,
        integration).

        :param plugin_dir: path of the directory which contains the plugins
            files.
        """
        self._load_description(plugin_dir)
        self.metadata = PluginMetadata(self.get_metadata_path(plugin_dir))
        self._load_integration(plugin_dir, webview)


def _logger():
    return logging.getLogger(__name__)


class ServiceManager:
    """
    Manages the list of available service integration plugins and
    provides a simple API for accessing the current service.

    """
    SV_DIR = 'services'

    @property
    def current_service(self):
        return Settings().current_service

    @current_service.setter
    def current_service(self, value):
        try:
            self._current = self.plugins[value]
        except KeyError:
            pass
        else:
            Settings().current_service = value

    def __init__(self, web_view):
        self._current = None
        self._plugins_path = []
        self.plugins = {}
        self._init_plugins_path()
        self._load_plugins(web_view)
        self._webview = web_view
        if self.current_service:
            self._current = self.plugins[self.current_service]

    def get_user_dir(self):
        if system.WINDOWS:
            user_dir = os.path.join(os.getenv('APPDATA') or '~',
                                    'MellowPlayer', self.SV_DIR)
        else:
            user_dir = os.path.join(
                os.path.expanduser('~'), '.local', 'share', 'mellowplayer',
                self.SV_DIR)
        # make sure user dir exists
        if not os.path.exists(user_dir):
            os.makedirs(user_dir)
        return user_dir

    def _init_plugins_path(self):
        """
        Initialises the plugins path.
        """
        _logger().debug('setting up plugins search path')
        sys_dir = '/usr/share/mellowplayer/%s' % self.SV_DIR
        if os.path.exists(sys_dir):
            self._plugins_path.append(sys_dir)
        user_dir = self.get_user_dir()
        if os.path.exists(user_dir):
            self._plugins_path.append(user_dir)
        app_dir = os.path.join(os.getcwd(), self.SV_DIR)
        if os.path.exists(app_dir):
            self._plugins_path.append(app_dir)
        # user workspace
        self._plugins_path.append(os.getcwd())
        _logger().info('service integrations plugin search path: %s',
                       ';'.join(self._plugins_path))

    def _add_plugin(self, path, plugin):
        name = plugin.metadata.name
        if name in self.plugins:
            _logger().warning('a service integration plugin '
                              'with the same name already '
                              'exists: <%s>', path)
        else:
            self.plugins[name] = plugin
            _logger().info('service integration plugin '
                           'successfully loaded: <%s>', path)

    def add_plugin(self, path, web_view):
        flg = False
        plugin_dir = os.path.abspath(os.path.join(path, os.pardir))
        if (os.path.isfile(path) or
                plugin_dir.startswith('.')):
            return flg
        _logger().debug('loading service integration plugin: <%s>',
                        path)
        invalid_files = ServicePlugin.check_required_files(path)
        if invalid_files:
            _logger().debug(
                'not a valid service integration plugin, '
                'invalid (or missing) plugin files: %r', invalid_files)
            return flg
        try:
            plugin = ServicePlugin(path, web_view)
        except Exception:
            # exception when loading plugin, just log it so that the plugin
            # developer knows what went wrong
            _logger().exception(
                'failed to load service integration plugin: <%s>',
                path)
        else:
            # Ok plugin loaded and validated
            flg = True
            self._add_plugin(path, plugin)
        return flg

    def _load_plugins(self, web_view):
        _logger().debug('loading plugins')
        # plugins from path
        for root in self._plugins_path:
            _logger().debug('inspecting potential plugin path: %s', root)
            flg = False
            for plugin_dir in os.listdir(root):
                path = os.path.join(root, plugin_dir)
                flg = self.add_plugin(path, web_view)
            if flg is False:
                _logger().debug('no valid services found in %s', root)
        # load user custom plugins.
        _logger().info('available services: %s',
                       ', '.join(self.plugins.keys()))

    def start_current_service(self):
        if self._current:
            self._start(self._current)
            return True
        return False

    def _start(self, service):
        _logger().info('starting service: %s', service.metadata.name)
        self._webview.load(QtCore.QUrl(service.metadata.url))
