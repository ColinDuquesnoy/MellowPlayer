#pragma once

#include <QSettings>
#include <MellowPlayer/UseCases.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class ApplicationSettings: public UseCases::IApplicationSettings {
public:
    ApplicationSettings();

    void clear() override;

    QString getCurrentService() const override;
    void setCurrentService(const QString& service) override;

    bool showCloseToSysemTrayMessage() const override;
    void setShowCloseToSystemTrayMessage(bool value) override;

    QVariant getValue(const QString& key, const QVariant& defaultValue) const override;
    void setValue(const QString& key, const QVariant& value) override;

    static const QString CURRENT_SERVICE_KEY;
    static const QString SHOW_CLOSE_TO_SYS_TRAY_MESSAGE_KEY;
private:
    QSettings qSettings;
};

END_MELLOWPLAYER_NAMESPACE
