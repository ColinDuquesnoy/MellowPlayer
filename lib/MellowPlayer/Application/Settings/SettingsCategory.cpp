#include "SettingsCategory.hpp"
#include "Setting.hpp"
#include "Settings.hpp"
#include <QtCore/QJsonObject>

using namespace std;
using namespace MellowPlayer::Application;

SettingsCategory::SettingsCategory(const SettingsCategory::Data& categoryData, Settings* appSettings) : QObject(appSettings), data(categoryData)
{
    for (int i = 0; i < data.parameters.count(); ++i) {
        QJsonObject parameterObj = data.parameters.at(i).toObject();
        Setting::Data settingData;
        settingData.name = parameterObj.value("name").toString();
        settingData.toolTip = parameterObj.value("tooltip").toString();
        settingData.type = parameterObj.value("type").toString();
        settingData.key = parameterObj.value("key").toString();
        settingData.defaultValue = parameterObj.value("default").toVariant();
        settingData.enableCondition = parameterObj.value("enabled").toString();
        settings.append(new Setting(*appSettings, *this, settingData));
    }
}

void SettingsCategory::resolveDependencies()
{
    for (Setting* setting : settings)
        setting->resolveDependency();
}

const QString& SettingsCategory::getName() const
{
    return data.name;
}

const QString& SettingsCategory::getIcon() const
{
    return data.icon;
}

const QString& SettingsCategory::getKey() const
{
    return data.key;
}

const QList<Setting*>& SettingsCategory::getSettings() const
{
    return settings;
}

Setting& SettingsCategory::getSetting(const QString& key) const
{
    for (Setting* param : settings)
        if (param->getKey() == key)
            return *param;
    throw runtime_error("Unknown setting: " + data.key.toStdString() + "/" + key.toStdString());
}

void SettingsCategory::restoreDefaults()
{
    for (Setting* setting : settings)
        setting->restoreDefaults();
}
