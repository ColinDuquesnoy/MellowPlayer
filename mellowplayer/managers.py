"""
This module contains our specialised plugin managers.
"""
import logging
import os
import sys

from yapsy.PluginManager import PluginManager

from . import system
from .api import plugins
from .qt import QtCore
from .settings import Settings


def _logger():
    return logging.getLogger(__name__)


class PluginsManager(PluginManager):
    def __init__(self):
        paths = self.get_plugins_paths()
        _logger().info('Plugin search paths: %r', paths)
        super().__init__(
            categories_filter={
                ServicesManager.CATEGORY: plugins.IServiceIntegrationPlugin,
                ExtensionsManager.CATEGORY: plugins.IExtensionPlugin
            },
            directories_list=paths, plugin_info_ext='plugin')
        self.collectPlugins()

    @classmethod
    def get_user_dir(cls):
        """
        Gets the plugins user directory (where new plugin should be
        installed)

        :returns: path to the user plugins directory
        :rtype: str
        """
        if system.WINDOWS:
            user_dir = os.path.join(os.getenv('APPDATA') or '~',
                                    'MellowPlayer', 'plugins')
        else:
            user_dir = os.path.join(
                os.path.expanduser('~'), '.local', 'data', 'mellowplayer',
                'plugins')
        # make sure user dir exists
        if not os.path.exists(user_dir):
            os.makedirs(user_dir)
        return user_dir

    @staticmethod
    def _append_plugin_path(path, paths):
        """
        Appends `path` to `paths` if `path` exists.

        :param path: path to check
        :param paths: the list of paths where to append `path`
        """
        if os.path.exists(path):
            paths.append(path)

    @classmethod
    def get_plugins_paths(cls):
        """
        Gets plugin search paths (list of str)
        """
        paths = []
        if system.LINUX:
            sys_dir = '%s/share/mellowplayer/plugins' % sys.prefix
            cls._append_plugin_path(sys_dir, paths)
        cls._append_plugin_path(cls.get_user_dir(), paths)
        # if running from source checkout
        dev_dir = os.path.join(os.getcwd(), 'data', 'plugins')
        cls._append_plugin_path(dev_dir, paths)
        return paths


class ServicesManager:
    CATEGORY = 'ServiceIntegration'

    @property
    def current_service_name(self):
        return Settings().current_service

    @current_service_name.setter
    def current_service_name(self, value):
        try:
            self.current_service = self.plugins[value]
        except KeyError:
            pass
        else:
            Settings().current_service = value

    def __init__(self, web_view, plugin_manager):
        """
        :type web_view: PyQt5.QtWebKitWidgets.QWebView
        :type plugin_manager: mellowplayer.core.plugins.PluginsManager
        """
        self._web_view = web_view
        self._plugin_manager = plugin_manager
        self.plugins = {}
        self.current_service = None
        for plugin_info in self._plugin_manager.getPluginsOfCategory(self.CATEGORY):
            plugin_manager.activatePluginByName(plugin_info.name, self.CATEGORY)
            service_plugin = plugin_info.plugin_object
            service_plugin.name = plugin_info.name
            service_plugin.maintainer_name = plugin_info.author
            service_plugin.maintainer_link = plugin_info.website
            service_plugin.version = plugin_info.version
            self.plugins[plugin_info.plugin_object.name] = service_plugin
            service_plugin.web_view = self._web_view
            if plugin_info.plugin_object.name == self.current_service_name:
                self.current_service = service_plugin

    def start_current_service(self):
        if self.current_service:
            self._start(self.current_service)
            return self.current_service
        return None

    def _start(self, service):
        _logger().info('starting service: %s', service.name)
        self._web_view.load(QtCore.QUrl(service.url))


class ExtensionsManager:
    CATEGORY = 'Extension'

    def __init__(self, plugin_manager, app):
        self._plugin_manager = plugin_manager
        for plugin_info in self._plugin_manager.getPluginsOfCategory(self.CATEGORY):
            plugin_manager.activatePluginByName(plugin_info.name, self.CATEGORY)
            plugin_info.plugin_object.setup(app)

    def teardown(self):
        for plugin_info in self._plugin_manager.getPluginsOfCategory(self.CATEGORY):
            plugin_info.plugin_object.teardown()
