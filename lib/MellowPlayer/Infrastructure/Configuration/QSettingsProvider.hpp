#pragma once

#include <QSettings>
#include <MellowPlayer/UseCases/Settings/ISettingsProvider.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class QSettingsProvider: public UseCases::ISettingsProvider {
public:
    QSettingsProvider();

    void clear() override;

    QString getCurrentService() const override;
    void setCurrentService(const QString& service) override;

    bool getShowCloseToSysemTrayMessage() const override;
    void setShowCloseToSystemTrayMessage(bool value) override;

    QVariant getValue(const QString& key, const QVariant& defaultValue=QVariant()) const override;
    void setValue(const QString& key, const QVariant& value) override;

    QString getTrayIcon() const override;
    void setTrayIcon(const QString& trayIcon) override;

    static const QString CURRENT_SERVICE_KEY;
    static const QString SHOW_CLOSE_TO_SYS_TRAY_MESSAGE_KEY;
    static const QString TRAY_ICON_KEY;

private:
    QSettings qSettings;
};

END_MELLOWPLAYER_NAMESPACE
