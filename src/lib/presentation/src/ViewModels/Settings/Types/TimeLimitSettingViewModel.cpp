#include <MellowPlayer/Presentation/ViewModels/Settings/Types/TimeLimitSettingViewModel.hpp>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Domain;

TimeLimitSettingViewModel::TimeLimitSettingViewModel(Setting& setting, QObject* parent) : SettingViewModel(setting, parent)
{
    TimeLimitSettingStrings strings;
    registerEnumTranslation(TimeLimits::Today, strings.today());
    registerEnumTranslation(TimeLimits::Yesterday, strings.yesterday());
    registerEnumTranslation(TimeLimits::LastWeek, strings.lastWeek());
    registerEnumTranslation(TimeLimits::LastMonth, strings.lastMonth());
    registerEnumTranslation(TimeLimits::LastYear, strings.lastYear());
    registerEnumTranslation(TimeLimits::Never, strings.never());
}

void TimeLimitSettingViewModel::registerEnumTranslation(TimeLimits value, const QString& translation)
{
    stringToEnum_[translation] = value;
    enumToString_[value] = translation;
}

QString TimeLimitSettingViewModel::value() const
{
    TimeLimits limit = static_cast<TimeLimits>(setting_.value().toInt());
    return enumToString_[limit];
}

void TimeLimitSettingViewModel::setValue(QString value)
{
    TimeLimits limit = stringToEnum_[value];
    setting_.setValue(static_cast<int>(limit));
}

void TimeLimitSettingViewModel::onValueChanged()
{
    emit valueChanged();
}

QString TimeLimitSettingViewModel::qmlComponent()
{
    return "Delegates/EnumSettingDelegate.qml";
}

QStringList TimeLimitSettingViewModel::values() const
{
    return stringToEnum_.keys();
}
