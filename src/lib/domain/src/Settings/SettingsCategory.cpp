#include <MellowPlayer/Domain/Settings/SettingsCategory.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>
#include <MellowPlayer/Domain/Settings/Settings.hpp>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

using namespace std;
using namespace MellowPlayer::Domain;

SettingsCategory::SettingsCategory(const SettingsCategory::Data& categoryData, Settings* appSettings) : QObject(appSettings), data_(categoryData)
{
    for (int i = 0; i < data_.parameters.count(); ++i) {
        QJsonObject parameterObj = data_.parameters.at(i).toObject();
        Setting::Data settingData;
        settingData.name = parameterObj.value("name").toString();
        settingData.toolTip = parameterObj.value("tooltip").toString();
        settingData.type = parameterObj.value("type").toString();
        settingData.key = parameterObj.value("key").toString();
        settingData.defaultValue = parameterObj.value("default").toVariant();
        settingData.enableCondition = parameterObj.value("enabled").toString();
        settings_.append(new Setting(*appSettings, *this, settingData));
    }
}

void SettingsCategory::resolveDependencies()
{
    for (Setting* setting : settings_)
        setting->resolveDependency();
}

const QString& SettingsCategory::name() const
{
    return data_.name;
}

const QString& SettingsCategory::icon() const
{
    return data_.icon;
}

const QString& SettingsCategory::key() const
{
    return data_.key;
}

const QList<Setting*>& SettingsCategory::toList() const
{
    return settings_;
}

Setting& SettingsCategory::get(const QString& key) const
{
    for (Setting* param : settings_)
        if (param->key() == key)
            return *param;
    throw runtime_error("Unknown setting: " + data_.key.toStdString() + "/" + key.toStdString());
}

QString SettingsCategory::toJavascriptObject()
{
    QJsonDocument document;
    QJsonObject jsonObject;
    for (auto* setting: toList()) {
        QString type = setting->type().toLower();
        if (type == "bool")
            jsonObject[setting->key()] = setting->value().toBool();
        else if (type == "int")
            jsonObject[setting->key()] = setting->value().toInt();
        else
            jsonObject[setting->key()] = setting->value().toString();
    }
    document.setObject(jsonObject);
    return QString::fromUtf8(document.toJson(QJsonDocument::Compact));
}

void SettingsCategory::restoreDefaults()
{
    for (Setting* setting : settings_)
        setting->restoreDefaults();
}
