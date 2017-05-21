#include <QtCore/QJsonObject>
#include "SettingsCategory.hpp"
#include "ApplicationSettings.hpp"
#include "Setting.hpp"

using namespace std;
USE_MELLOWPLAYER_NAMESPACE(UseCases)

SettingsCategory::SettingsCategory(const SettingsCategory::Data& categoryData,
                                   ApplicationSettings* appSettings): QObject(appSettings), data(categoryData) {
    for(int i = 0; i < data.parameters.count(); ++i) {
        QJsonObject parameterObj = data.parameters.at(i).toObject();
        Setting::Data settingData;
        settingData.name = parameterObj.value("name").toString();
        settingData.type = parameterObj.value("type").toString();
        settingData.key = parameterObj.value("key").toString();
        settingData.defaultValue = parameterObj.value("default").toVariant();
        settingData.enableCondition = parameterObj.value("enabled").toString();
        settings.append(new Setting(*appSettings, *this, settingData));
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

Setting& SettingsCategory::getSetting(const QString& key) const {
    for(Setting* param: settings)
        if (param->getKey() == key)
            return *param;
    throw runtime_error("Unknown setting: " + data.key.toStdString() + "/" + key.toStdString());
}
