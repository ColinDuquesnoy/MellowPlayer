"""
This module contains the cloud music service API.
"""
import configparser
import importlib.machinery
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

    def _load(self, plugin_dir, webview):
        """
        Loads a plugin from the 3 required files (metadata, description,
        integration).

        :param plugin_dir: path of the directory which contains the plugins
            files.
        """
        with open(os.path.join(plugin_dir, self.FN_DESCRIPTION), 'r') as f:
            self.description = f.read()
        self.metadata = PluginMetadata(os.path.join(
            plugin_dir, self.FN_METADATA))

        module = os.path.join(plugin_dir, 'integration.py')
        name ='%s_%s' % (
            os.path.split(module)[1].replace('.py', ''),
            self.metadata.name.lower())
        loader = importlib.machinery.SourceFileLoader(name, module)
        plugin_module = loader.load_module()
        loaded_class = getattr(plugin_module, '%sServiceIntegration' %
                               self.metadata.name)
        self.integration = loaded_class(webview)


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
        app_dir = os.path.join(os.getcwd(), self.SV_DIR)
        if platform.system().lower() == 'windows':
            user_dir = os.path.join(os.getenv('APPDATA') or '~',
                                    'MellowPlayer', self.SV_DIR)
        else:
            # 2 places on linux and osx (user place and system place)
            sys_dir = '/usr/share/mellowplayer/%s' % self.SV_DIR
            self._plugins_path.append(sys_dir)
            user_dir = os.path.join('~/.local/share/mellowplayer', self.SV_DIR)
        user_dir = os.path.expanduser(user_dir)
        if not os.path.exists(user_dir):
            # make sure user dir exists
            os.makedirs(user_dir)
        self._plugins_path.append(app_dir)
        self._plugins_path.append(user_dir)
        # user workspace
        self._plugins_path.append(os.getcwd())

    def _load_plugins(self, webview):
        for root in self._plugins_path:
            print('inspecting potential plugin path: %s' % root)
            flg = False
            try:
                for plugin_dir in os.listdir(root):
                    plugin_dir = os.path.join(root, plugin_dir)
                    print('trying to load service: %s' % plugin_dir)
                    try:
                        plugin = ServicePlugin(plugin_dir, webview)
                    except (OSError,
                            configparser.NoOptionError) as e:
                        # invalid plugin dir
                        print('invalid service plugin: %s' % plugin_dir)
                    else:
                        flg = True
                        self._plugins[plugin.metadata.name] = plugin
            except OSError:
                # no services directory, continue with next path
                print('directory not found: %s' % root)
            else:
                if flg is False:
                    print('no valid services found in %s' % root)
        print('available service integration plugins: %r' %
              list(self._plugins.keys()))

    def start(self, service_name):
        service = self._plugins[service_name]
        self._webview.load(QtCore.QUrl(service.metadata.url))
