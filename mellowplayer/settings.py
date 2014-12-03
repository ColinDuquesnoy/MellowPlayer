"""
This module provides an interface to the application settings (get/set)
"""
from mellowplayer import system
from mellowplayer.qt import QtCore, to_string, to_bool


class Settings(QtCore.QSettings):
    def __init__(self):
        super().__init__('mellowplayer')

    @property
    def flg_close(self):
        return to_bool(self.value('flg_close', 'False'))

    @flg_close.setter
    def flg_close(self, val):
        self.setValue('flg_close', repr(val))

    @property
    def exit_on_close_if_not_playing(self):
        return to_bool(self.value('exit_on_close_if_not_playing', 'True'))

    @exit_on_close_if_not_playing.setter
    def exit_on_close_if_not_playing(self, value):
        self.setValue('exit_on_close_if_not_playing', repr(value))

    @property
    def cookies(self):
        str_val = to_string(self.value('cookies'))
        if str_val:
            return eval(str_val)
        return None

    @cookies.setter
    def cookies(self, value):
        self.setValue('cookies', value)

    @property
    def current_service(self):
        return to_string(self.value('current_service'))

    @current_service.setter
    def current_service(self, value):
        self.setValue('current_service', str(value))

    @property
    def always_show_tray_icon(self):
        return to_bool(self.value(
            'always_show_tray_icon', 'True'))

    @always_show_tray_icon.setter
    def always_show_tray_icon(self, value):
        self.setValue('always_show_tray_icon', repr(value))

    @property
    def tray_icon(self):
        def default_icon():
            if system.WINDOWS:
                return ':/mellowplayer-tray-dark.svg'
            if system.DARWIN or system.linux_distribution == 'KaOS':
                return ':/mellowplayer-tray-light.svg'
            return ':/application-x-mellowplayer.png'
        return to_string(self.value('tray_icon', default_icon()))
