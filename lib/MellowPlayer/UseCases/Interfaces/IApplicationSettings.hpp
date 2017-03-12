#pragma once

#include <QString>
#include <QVariant>
#include <MellowPlayer/Macros.hpp>
#include "../Notifications/Notifications.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class IApplicationSettings
{
public:
    virtual ~IApplicationSettings() = default;

    virtual void clear() = 0;

    virtual QString getCurrentService() const = 0;
    virtual void setCurrentService(const QString& service) = 0;

    virtual bool getShowCloseToSysemTrayMessage() const = 0;
    virtual void setShowCloseToSystemTrayMessage(bool value) = 0;

    virtual QString getTrayIcon() const = 0;
    virtual void setTrayIcon(const QString& trayIcon) = 0;

    virtual QVariant getValue(const QString& key, const QVariant& defaultValue = QVariant()) const = 0;
    virtual void setValue(const QString& key, const QVariant& value) = 0;

    virtual bool getNotificationsEnabled() const = 0;
    virtual void setNotificationsEnabled(bool enable) = 0;

    virtual bool isNotificationTypeEnabled(NotificationType notificationType) const = 0;
    virtual void enableNotificationType(NotificationType notificationType, bool enable) = 0;
};

END_MELLOWPLAYER_NAMESPACE