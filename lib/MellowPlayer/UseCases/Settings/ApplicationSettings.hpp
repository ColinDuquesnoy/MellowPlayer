#pragma once

#include <QtCore/QObject>
#include <QtCore/QList>
#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class ISettingsProvider;
class ISettingsSchemaLoader;
class SettingsCategory;
class Setting;

class ApplicationSettings: public QObject {
    Q_OBJECT
public:
    ApplicationSettings(ISettingsSchemaLoader& configurationLoader, ISettingsProvider& settingsProvider);

    const QList<SettingsCategory*>& getCategories() const;

    const SettingsCategory* getCategory(const QString& key) const;
    Setting* getSetting(const QString& key) const;

private:
    QList<SettingsCategory*> categories;
};

END_MELLOWPLAYER_NAMESPACE
