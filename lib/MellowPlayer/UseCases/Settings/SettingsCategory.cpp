#include <QtCore/QJsonObject>
#include "SettingsCategory.hpp"
#include "ApplicationSettings.hpp"
#include "Setting.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)

SettingsCategory::SettingsCategory(ISettingsProvider& settingsProvider, const SettingsCategory::Data& data,
                               ApplicationSettings* appSettings): QObject(appSettings), data(data) {
    for(int i = 0; i < data.parameters.count(); ++i) {
        QJsonObject parameterObj = data.parameters.at(i).toObject();
        Setting::Data data;
        data.name = parameterObj.value("name").toString();
        data.type = parameterObj.value("type").toString();
        data.key = parameterObj.value("key").toString();
        data.defaultValue = parameterObj.value("default").toVariant();
        data.enableCondition = parameterObj.value("enabled").toString();
        settings.append(new Setting(settingsProvider, *appSettings, *this, data));
    }
}

void SettingsCategory::resolveDependencies() {
    for(Setting* setting: settings)
        setting->resolveDependency();
}

const QString& SettingsCategory::getName() const {
    return data.name;
}

const QString& SettingsCategory::getIcon() const {
    return data.icon;
}

const QString& SettingsCategory::getKey() const {
    return data.key;
}

const QList<Setting*>& SettingsCategory::getSettings() const {
    return settings;
}

Setting* SettingsCategory::getSetting(const QString& key) const {
    for(Setting* param: settings)
        if (param->getKey() == key)
            return param;
    return nullptr;
}
