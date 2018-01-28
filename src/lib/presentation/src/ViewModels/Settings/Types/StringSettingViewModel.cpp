#include <MellowPlayer/Presentation/ViewModels/Settings/Types/StringSettingViewModel.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Domain;

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
    return "Delegates/StringSettingDelegate.qml";
}
