#pragma once

#include "SettingKey.hpp"
#include <QtCore/QList>
#include <QtCore/QObject>

namespace MellowPlayer::Domain
{
    class ISettingsProvider;
    class ISettingsSchemaLoader;
    class SettingsCategory;
    class Setting;

    class Settings : public QObject
    {
        Q_OBJECT
    public:
        Settings(ISettingsSchemaLoader& configurationLoader, ISettingsProvider& settingsProvider);

        const QList<SettingsCategory*>& categories() const;

        SettingsCategory& category(const QString& key) const;
        Setting& get(const QString& key) const;
        Setting& get(SettingKey::Keys key);

        ISettingsProvider& settingsProvider() const;

        void restoreDefaults();

    private:
        ISettingsProvider& settingsProvider_;
        QList<SettingsCategory*> categories_;
    };
}
