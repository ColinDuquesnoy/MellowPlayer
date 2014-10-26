"""
This module provides an interface to the application settings (get/set)
"""
from PyQt4 import QtCore


class Settings(QtCore.QSettings):
    def __init__(self):
        super().__init__('mellowplayer')

    @property
    def flg_close(self):
        return eval(self.value('flg_close', 'False'))

    @flg_close.setter
    def flg_close(self, val):
        self.setValue('flg_close', repr(val))

    @property
    def cookies(self):
        return self.value('cookies')

    @cookies.setter
    def cookies(self, value):
        self.setValue('cookies', value)

    @property
    def current_service(self,):
        return self.value('current_service', '')

    @current_service.setter
    def current_service(self, value):
        self.setValue('current_service', value)

    @property
    def always_show_tray_icon(self):
        return eval(self.value('always_show_tray_icon', 'True'))

    @always_show_tray_icon.setter
    def always_show_tray_icon(self, value):
        self.setValue('always_show_tray_icon', repr(value))
