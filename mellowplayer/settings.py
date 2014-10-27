"""
This module provides an interface to the application settings (get/set)
"""
from PyQt4 import QtCore


class Settings(QtCore.QSettings):
    def __init__(self):
        super().__init__('mellowplayer')

    @property
    def flg_close(self):
        return eval(str(self.value(
            'flg_close', 'False').toPyObject()))

    @flg_close.setter
    def flg_close(self, val):
        self.setValue('flg_close', repr(val))

    @property
    def exit_on_close_if_not_playing(self):
        return eval(str(self.value(
            'exit_on_close_if_not_playing', 'True').toPyObject()))

    @exit_on_close_if_not_playing.setter
    def exit_on_close_if_not_playing(self, value):
        self.setValue('exit_on_close_if_not_playing', repr(value))

    @property
    def cookies(self):
        return str(self.value('cookies').toPyObject())

    @cookies.setter
    def cookies(self, value):
        self.setValue('cookies', value)

    @property
    def current_service(self):
        return str(self.value(
            'current_service', '').toPyObject())

    @current_service.setter
    def current_service(self, value):
        self.setValue('current_service', QtCore.QSettings(value))

    @property
    def always_show_tray_icon(self):
        return eval(str(self.value(
            'always_show_tray_icon', 'True').toPyObject()))

    @always_show_tray_icon.setter
    def always_show_tray_icon(self, value):
        self.setValue('always_show_tray_icon', repr(value))
