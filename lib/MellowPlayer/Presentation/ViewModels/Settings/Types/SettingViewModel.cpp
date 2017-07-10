#include "SettingViewModel.hpp"
#include <QDebug>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;

SettingViewModel::SettingViewModel(Setting& setting, QObject* parent): QObject(parent), setting(setting) {
    connect(&setting, &Setting::valueChanged, this, &SettingViewModel::onValueChanged);
    connect(&setting, &Setting::isEnabledChanged, this, &SettingViewModel::onIsEnabledChanged);
}

QString SettingViewModel::getName() const {
    return setting.getName();
}

QString SettingViewModel::getToolTip() const {
    return setting.getToolTip();
}

QString SettingViewModel::getType() const {
    return setting.getType();
}

bool SettingViewModel::getEnabled() const {
    return setting.isEnabled();
}

void SettingViewModel::onIsEnabledChanged()
{
    emit enabledChanged();
}
