#include "MellowPlayer/Presentation/ViewModels/Settings/Types/TimeLimitSettingViewModel.hpp"

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Application;

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
    stringToEnum[translation] = value;
    enumToString[value] = translation;
}

QString TimeLimitSettingViewModel::getValue() const
{
    TimeLimits limit = static_cast<TimeLimits>(setting.getValue().toInt());
    return enumToString[limit];
}

void TimeLimitSettingViewModel::setValue(QString value)
{
    TimeLimits limit = stringToEnum[value];
    setting.setValue(static_cast<int>(limit));
}

void TimeLimitSettingViewModel::onValueChanged()
{
    emit valueChanged();
}

QString TimeLimitSettingViewModel::getQmlComponent()
{
    return "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/Delegates/EnumSettingDelegate.qml";
}

QStringList TimeLimitSettingViewModel::getValues() const
{
    return stringToEnum.keys();
}