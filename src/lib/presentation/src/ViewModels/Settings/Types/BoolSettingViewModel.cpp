#include <MellowPlayer/Presentation/ViewModels/Settings/Types/BoolSettingViewModel.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Domain;

BoolSettingViewModel::BoolSettingViewModel(Setting& setting, QObject* parent) : SettingViewModel(setting, parent)
{
}

bool BoolSettingViewModel::getValue() const
{
    return setting_.value().toBool();
}

void BoolSettingViewModel::setValue(bool value)
{
    setting_.setValue(value);
}

void BoolSettingViewModel::onValueChanged()
{
    emit valueChanged();
}

QString BoolSettingViewModel::qmlComponent()
{
    return "Delegates/BoolSettingDelegate.qml";
}
