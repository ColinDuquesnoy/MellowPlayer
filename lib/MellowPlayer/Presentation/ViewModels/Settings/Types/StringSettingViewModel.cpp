#include "StringSettingViewModel.hpp"
#include <MellowPlayer/Application/Settings/Setting.hpp>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Application;

StringSettingViewModel::StringSettingViewModel(Setting& setting, QObject* parent) : SettingViewModel(setting, parent)
{
}

QString StringSettingViewModel::getValue() const
{
    return setting_.value().toString();
}

void StringSettingViewModel::setValue(QString value)
{
    setting_.setValue(value);
}

void StringSettingViewModel::onValueChanged()
{
    emit valueChanged();
}

QString StringSettingViewModel::qmlComponent()
{
    return "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/Delegates/StringSettingDelegate.qml";
}
