#include <QtCore/QVariant>
#include "Setting.hpp"
#include "SettingsCategory.hpp"
#include "ApplicationSettings.hpp"
#include "ISettingsProvider.hpp"
#include <QDebug>

using namespace std;
USE_MELLOWPLAYER_NAMESPACE(UseCases)

Setting::Setting(ApplicationSettings& appSettings, SettingsCategory& category, const Setting::Data& data) :
        QObject(&category), settingsProvider(appSettings.getSettingsProvider()), appSettings(appSettings),
        category(category), data(data) {
}

void Setting::resolveDependency() {
    if (data.enableCondition.startsWith("!"))
        notOperator = true;

    QString key = QString(data.enableCondition);
    key = key.replace("!", "");

    try {
        parentSetting = &appSettings.getSetting(key);
        if (parentSetting->getType() == "bool")
            connect(parentSetting, &Setting::valueChanged, this, &Setting::onParentValueChanged);
    }
    catch (const runtime_error& e) {
        return;
    }
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
