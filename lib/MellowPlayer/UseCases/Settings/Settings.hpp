#pragma once

#include <QtCore/QObject>
#include <QtCore/QList>
#include <MellowPlayer/Macros.hpp>
#include "SettingKey.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class ISettingsProvider;
class ISettingsSchemaLoader;
class SettingsCategory;
class Setting;

class Settings: public QObject {
    Q_OBJECT
public:
    Settings(ISettingsSchemaLoader& configurationLoader, ISettingsProvider& settingsProvider);

    const QList<SettingsCategory*>& getCategories() const;

    SettingsCategory& getCategory(const QString& key) const;
    Setting& get(const QString& key) const;
    Setting& get(SettingKey::Keys key);

    ISettingsProvider& getSettingsProvider() const;

private:
    ISettingsProvider& settingsProvider;
    QList<SettingsCategory*> categories;
};

END_MELLOWPLAYER_NAMESPACE
