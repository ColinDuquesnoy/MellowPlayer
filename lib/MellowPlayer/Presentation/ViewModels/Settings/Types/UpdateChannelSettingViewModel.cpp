#include "UpdateChannelSettingViewModel.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

UpdateChannelSettingViewModel::UpdateChannelSettingViewModel(Setting& setting, QObject* parent)
    : SettingViewModel(setting, parent)
{

}

QString UpdateChannelSettingViewModel::getValue() const
{
    UpdateChannel channel = static_cast<UpdateChannel>(setting.getValue().toInt());
    return stringer_.toString(channel);
}

QStringList UpdateChannelSettingViewModel::getValues() const
{
    return QStringList() << stringer_.toString(UpdateChannel::Stable) <<
                            stringer_.toString(UpdateChannel::Beta) <<
                            stringer_.toString(UpdateChannel::Continuous);
}

QString UpdateChannelSettingViewModel::getQmlComponent()
{
    return "qrc:/MellowPlayer/Presentation/Views/MellowPlayer/Delegates/EnumSettingDelegate.qml";
}

void UpdateChannelSettingViewModel::setValue(QString value)
{
    setting.setValue(static_cast<int>(stringer_.fromString(value)));
}
void UpdateChannelSettingViewModel::onValueChanged()
{
    emit valueChanged();
}
