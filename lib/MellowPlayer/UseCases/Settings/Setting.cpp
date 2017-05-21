#include <QtCore/QVariant>
#include "Setting.hpp"
#include "SettingsCategory.hpp"
#include "ApplicationSettings.hpp"
#include "ISettingsProvider.hpp"
#include <QDebug>

USE_MELLOWPLAYER_NAMESPACE(UseCases)

Setting::Setting(ISettingsProvider& settingsProvider, ApplicationSettings& appSettings, SettingsCategory& category,
                 const Setting::Data& data) :
        QObject(&category), settingsProvider(settingsProvider), appSettings(appSettings), category(category),
        data(data) {

    resolveDependency();
}

void Setting::resolveDependency() {
    if (data.enableCondition.startsWith("!"))
        notOperator = true;

    QString key = QString(data.enableCondition);
    key = key.replace("!", "");
    parentSetting = appSettings.getSetting(key);

    if (parentSetting && parentSetting->getType() == "bool")
        connect(parentSetting, &Setting::valueChanged, this, &Setting::onParentValueChanged);
}

const QString& Setting::getKey() const {
    return data.key;
}

const QString& Setting::getName() const {
    return data.name;
}

const QString& Setting::getType() const {
    return data.type;
}

QVariant Setting::getDefaultValue() const {
    return data.defaultValue;
}

QVariant Setting::getValue() const {
    return settingsProvider.getValue(getFullKey(), data.defaultValue);
}

void Setting::setValue(const QVariant& value) {
    if (value != getValue()) {
        settingsProvider.setValue(getFullKey(), value);
        emit valueChanged();
    }
}

bool Setting::isEnabled() const {
    std::string cond = data.enableCondition.toStdString();

    if (parentSetting == nullptr)
        return true;

    bool parentValue = parentSetting->getValue().toBool();

    if (notOperator)
        return !parentValue;

    return parentValue;
}

QString Setting::getFullKey() const {
    return category.getKey() + "/" + data.key;
}

void Setting::onParentValueChanged() {
    emit isEnabledChanged();
}
