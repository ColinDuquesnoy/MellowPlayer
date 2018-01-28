#pragma once

#include <MellowPlayer/Domain/Settings/SettingKey.hpp>
#include <QtCore/QList>
#include <QtCore/QObject>

namespace MellowPlayer::Domain
{
    class ISettingsStore;
    class ISettingsSchemaLoader;
    class SettingsCategory;
    class Setting;

    class Settings : public QObject
    {
        Q_OBJECT
    public:
        Settings(ISettingsSchemaLoader& configurationLoader, ISettingsStore& settingsStore);

        const QList<SettingsCategory*>& categories() const;

        SettingsCategory& category(const QString& key) const;
        Setting& get(const QString& key) const;
        Setting& get(SettingKey::Keys key);

        ISettingsStore& store() const;

        void restoreDefaults();

    private:
        ISettingsStore& settingsStore_;
        QList<SettingsCategory*> categories_;
    };
}
