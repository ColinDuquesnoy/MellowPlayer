"""
This module contains the cloud music service API.
"""
import configparser
import importlib.machinery
import logging
import os
import platform
from PyQt4 import QtCore


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
        try:
            self.icon = config.get(self.SECTION, 'version_minor')
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
    def check_required_paths(cls, plugin_dir):
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
        return None

    def __init__(self, web_view):
        self._plugins_path = []
        self._plugins = {}
        self._init_plugins_path()
        self._load_plugins(web_view)
        self._webview = web_view

    def _init_plugins_path(self):
        """
        Initialises the plugins path.
        """
        _logger().debug('setting up plugins search path')
        app_dir = os.path.join(os.getcwd(), self.SV_DIR)
        if platform.system().lower() == 'windows':
            user_dir = os.path.join(os.getenv('APPDATA') or '~',
                                    'MellowPlayer', self.SV_DIR)
        else:
            # 2 places on linux and osx (user place and system place)
            sys_dir = '/usr/share/mellowplayer/%s' % self.SV_DIR
            if os.path.exists(sys_dir):
                self._plugins_path.append(sys_dir)
            user_dir = os.path.join('~/.local/share/mellowplayer', self.SV_DIR)
        user_dir = os.path.expanduser(user_dir)
        if not os.path.exists(user_dir):
            # make sure user dir exists
            os.makedirs(user_dir)
        if os.path.exists(app_dir):
            self._plugins_path.append(app_dir)
        if os.path.exists(user_dir):
            self._plugins_path.append(user_dir)
        # user workspace
        self._plugins_path.append(os.getcwd())
        _logger().info('service integrations plugin search path: %s',
                       ';'.join(self._plugins_path))

    def _add_plugin(self, path, plugin):
        name = plugin.metadata.name
        if name in self._plugins:
            _logger().warning('a service integration plugin '
                              'with the same name already '
                              'exists: <%s>', path)
        else:
            self._plugins[name] = plugin
            _logger().info('service integration plugin '
                           'successfully loaded: <%s>', path)

    def _load_plugins(self, webview):
        _logger().debug('loading plugins')
        for root in self._plugins_path:
            _logger().debug('inspecting potential plugin path: %s', root)
            flg = False
            for plugin_dir in os.listdir(root):
                path = os.path.join(root, plugin_dir)
                if (os.path.isfile(path) or
                        plugin_dir.startswith('.')):
                    continue
                _logger().debug('loading service integration plugin: <%s>',
                                path)
                missing_files = ServicePlugin.check_required_paths(path)
                if missing_files:
                    _logger().debug(
                        'not a valid service integration plugin, '
                        'cannot find required plugin files: %r', missing_files)
                    continue
                try:
                    plugin = ServicePlugin(path, webview)
                except Exception:
                    # invalid plugin dir, just log why the loading failed
                    _logger().exception(
                        'failed to load service integration plugin: <%s>',
                        path)
                else:
                    flg = True
                    self._add_plugin(path, plugin)
            if flg is False:
                _logger().debug('no valid services found in %s', root)
        _logger().info('available services: %s',
                       ', '.join(self._plugins.keys()))

    def start(self, service_name):
        service = self._plugins[service_name]
        _logger().info('starting service: %s', service_name)
        self._webview.load(QtCore.QUrl(service.metadata.url))
