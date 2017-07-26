#include "TimeLimitSettingViewModel.hpp"

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Application;

TimeLimitSettingViewModel::TimeLimitSettingViewModel(Setting& setting, QObject* parent) : SettingViewModel(setting, parent)
{
    registerEnumTranslation(TimeLimits::Today, tr("Today"));
    registerEnumTranslation(TimeLimits::Yesterday, tr("Yesterday"));
    registerEnumTranslation(TimeLimits::LastWeek, tr("Last week"));
    registerEnumTranslation(TimeLimits::LastMonth, tr("Last month"));
    registerEnumTranslation(TimeLimits::LastYear, tr("Last year"));
    registerEnumTranslation(TimeLimits::Never, tr("Never"));
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
    return "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/Delegates/"
           "EnumSettingDelegate.qml";
}

QStringList TimeLimitSettingViewModel::getValues() const
{
    return stringToEnum.keys();
}
