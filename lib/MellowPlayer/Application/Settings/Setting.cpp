#include <QtCore/QVariant>
#include "Setting.hpp"
#include "SettingsCategory.hpp"
#include "Settings.hpp"
#include "ISettingsProvider.hpp"
#include <QDebug>

using namespace std;
USE_MELLOWPLAYER_NAMESPACE(Application)

Setting::Setting(Settings& settings, SettingsCategory& category, const Setting::Data& settingData) :
        QObject(&category), settingsProvider(settings.getSettingsProvider()), settings(settings),
        category(category), data(settingData) {
}

void Setting::resolveDependency() {
    if (data.enableCondition.startsWith("!"))
        notOperator = true;

    QString key = QString(data.enableCondition);
    key = key.replace("!", "");

    if (key.isEmpty())
        return;

    try {
        parentSetting = &settings.get(key);
        if (parentSetting->getType() == "bool")
            connect(parentSetting, &Setting::valueChanged, this, &Setting::onParentValueChanged);
    }
    catch (const runtime_error&) {
        return;
    }
}

void Setting::restoreDefaults() {
    setValue(data.defaultValue);
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

const QString& Setting::getToolTip() const {
    return data.toolTip;
}
