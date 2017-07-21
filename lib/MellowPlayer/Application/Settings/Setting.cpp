#include "Setting.hpp"
#include "ISettingsProvider.hpp"
#include "Settings.hpp"
#include "SettingsCategory.hpp"
#include <QDebug>
#include <QtCore/QVariant>

using namespace std;
using namespace MellowPlayer::Application;

Setting::Setting(Settings &settings, SettingsCategory &category, const Setting::Data &settingData)
        : QObject(&category), settingsProvider(settings.getSettingsProvider()), settings(settings), category(category), data(settingData)
{
}

void Setting::resolveDependency()
{
    //    if (data.enableCondition.startsWith("!"))
    //        notOperator = true;

    QString key = QString(data.enableCondition);
    key = key.replace("!", "");
    key = key.split("==")[0].trimmed();

    if (key.isEmpty())
        return;

    try {
        parentSetting = &settings.get(key);
        connect(parentSetting, &Setting::valueChanged, this, &Setting::onParentValueChanged);
    } catch (const runtime_error &) {
        return;
    }
}

void Setting::restoreDefaults()
{
    setValue(data.defaultValue);
}

const QString &Setting::getKey() const
{
    return data.key;
}

const QString &Setting::getName() const
{
    return data.name;
}

const QString &Setting::getType() const
{
    return data.type;
}

QVariant Setting::getDefaultValue() const
{
    return data.defaultValue;
}

QVariant Setting::getValue() const
{
    return settingsProvider.getValue(getFullKey(), data.defaultValue);
}

void Setting::setValue(const QVariant &value)
{
    if (value != getValue()) {
        settingsProvider.setValue(getFullKey(), value);
        emit valueChanged();
    }
}

bool Setting::isEnabled() const
{
    QString cond = data.enableCondition;

    if (parentSetting == nullptr)
        return true;

    if (cond.contains("==")) {
        QString value = cond.split("==")[1].trimmed().toLower();
        QString parentValue = parentSetting->getValue().toString();
        return parentValue.trimmed().toLower() == value;
    } else {
        bool parentValue = parentSetting->getValue().toBool();

        //        if (notOperator)
        //            return !parentValue;

        return parentValue;
    }
}

QString Setting::getFullKey() const
{
    return category.getKey() + "/" + data.key;
}

void Setting::onParentValueChanged()
{
    emit isEnabledChanged();
}

const QString &Setting::getToolTip() const
{
    return data.toolTip;
}
