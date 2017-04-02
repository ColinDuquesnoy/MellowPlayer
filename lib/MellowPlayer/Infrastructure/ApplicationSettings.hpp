#pragma once

#include <QSettings>
#include <MellowPlayer/UseCases/Interfaces/IApplicationSettings.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class ApplicationSettings: public UseCases::IApplicationSettings {
public:
    ApplicationSettings();

    void clear() override;

    QString getCurrentService() const override;
    void setCurrentService(const QString& service) override;

    bool getShowCloseToSysemTrayMessage() const override;
    void setShowCloseToSystemTrayMessage(bool value) override;

    QVariant getValue(const QString& key, const QVariant& defaultValue=QVariant()) const override;
    void setValue(const QString& key, const QVariant& value) override;

    QString getTrayIcon() const override;
    void setTrayIcon(const QString& trayIcon) override;

    bool getNotificationsEnabled() const override;
    void setNotificationsEnabled(bool enable) override;

    bool isNotificationTypeEnabled(Entities::NotificationType notificationType) const override;
    void enableNotificationType(Entities::NotificationType notificationType, bool enable) override;

    static const QString CURRENT_SERVICE_KEY;
    static const QString SHOW_CLOSE_TO_SYS_TRAY_MESSAGE_KEY;
    static const QString TRAY_ICON_KEY;
    static const QString NOTIFICATIONS_ENABLED_KEY;
    static const QString NOTIFICATION_ENABLED_KEY;
private:
    QString getNotificationEnabledKey(Entities::NotificationType type) const;

    QSettings qSettings;
};

END_MELLOWPLAYER_NAMESPACE
