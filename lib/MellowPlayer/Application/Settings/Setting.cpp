#include "Setting.hpp"
#include "ISettingsProvider.hpp"
#include "Settings.hpp"
#include "SettingsCategory.hpp"

using namespace std;
using namespace MellowPlayer::Application;

Setting::Setting(Settings& settings, SettingsCategory& category, const Setting::Data& settingData)
        : QObject(&category), settingsProvider_(settings.settingsProvider()), settings_(settings), category_(category), data_(settingData)
{
}

void Setting::resolveDependency()
{
    //    if (data.enableCondition.startsWith("!"))
    //        notOperator_ = true;

    QString key(data_.enableCondition);
    key = key.replace("!", "");
    key = key.split("==")[0].trimmed();

    if (key.isEmpty())
        return;

    try {
        parentSetting_ = &settings_.get(key);
        connect(parentSetting_, &Setting::valueChanged, this, &Setting::onParentValueChanged);
    } catch (const runtime_error&) {
        return;
    }
}

void Setting::restoreDefaults()
{
    setValue(data_.defaultValue);
}

const QString& Setting::key() const
{
    return data_.key;
}

const QString& Setting::name() const
{
    return data_.name;
}

const QString& Setting::type() const
{
    return data_.type;
}

QVariant Setting::defaultValue() const
{
    return data_.defaultValue;
}

QVariant Setting::value() const
{
    return settingsProvider_.value(getFullKey(), data_.defaultValue);
}

void Setting::setValue(const QVariant& newValue)
{
    if (newValue != value()) {
        settingsProvider_.setValue(getFullKey(), newValue);
        emit valueChanged();
    }
}

bool Setting::isEnabled() const
{
    QString cond = data_.enableCondition;

    if (parentSetting_ == nullptr)
        return true;

    if (cond.contains("==")) {
        QString value = cond.split("==")[1].trimmed().toLower();
        QString parentValue = parentSetting_->value().toString();
        return parentValue.trimmed().toLower() == value;
    } else {
        bool parentValue = parentSetting_->value().toBool();

        //        if (notOperator_)
        //            return !parentValue;

        return parentValue;
    }
}

QString Setting::getFullKey() const
{
    return category_.key() + "/" + data_.key;
}

void Setting::onParentValueChanged()
{
    emit isEnabledChanged();
}

const QString& Setting::toolTip() const
{
    return data_.toolTip;
}
