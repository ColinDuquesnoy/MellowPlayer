#include <MellowPlayer/Presentation/ViewModels/Settings/Types/SettingViewModel.hpp>
#include <MellowPlayer/Domain/Settings/Setting.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

SettingViewModel::SettingViewModel(Setting& setting, QObject* parent) : QObject(parent), setting_(setting)
{
    connect(&setting, &Setting::valueChanged, this, &SettingViewModel::onValueChanged);
    connect(&setting, &Setting::isEnabledChanged, this, &SettingViewModel::onEnabledChanged);
}

QString SettingViewModel::name() const
{
    return setting_.name();
}

QString SettingViewModel::toolTip() const
{
    return setting_.toolTip();
}

QString SettingViewModel::type() const
{
    return setting_.type();
}

bool SettingViewModel::enabled() const
{
    return setting_.isEnabled();
}

void SettingViewModel::onEnabledChanged()
{
    emit enabledChanged();
}
