#include "ApplicationSettingsMock.hpp"

QString ApplicationSettingsMock::currentService = "";
QMap<NotificationType, bool> ApplicationSettingsMock::enabledNotifications;
bool ApplicationSettingsMock::notificationsEnabled = true;