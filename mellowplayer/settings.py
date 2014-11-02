"""
This module provides an interface to the application settings (get/set)
"""
from PyQt4 import QtCore
from mellowplayer import system


class Settings(QtCore.QSettings):
    def __init__(self):
        super().__init__('mellowplayer')

    @property
    def flg_close(self):
        return self.value('flg_close', 'False').toBool()

    @flg_close.setter
    def flg_close(self, val):
        self.setValue('flg_close', repr(val))

    @property
    def exit_on_close_if_not_playing(self):
        return self.value('exit_on_close_if_not_playing', 'True').toBool()

    @exit_on_close_if_not_playing.setter
    def exit_on_close_if_not_playing(self, value):
        self.setValue('exit_on_close_if_not_playing', repr(value))

    @property
    def cookies(self):
        str_val = str(self.value('cookies').toString())
        if str_val:
            return eval(str_val)
        return None

    @cookies.setter
    def cookies(self, value):
        self.setValue('cookies', value)

    @property
    def current_service(self):
        return self.value('current_service').toString()

    @current_service.setter
    def current_service(self, value):
        self.setValue('current_service', value)

    @property
    def always_show_tray_icon(self):
        return self.value(
            'always_show_tray_icon', 'True').toBool()

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
        return self.value('tray_icon', default_icon()).toString()
