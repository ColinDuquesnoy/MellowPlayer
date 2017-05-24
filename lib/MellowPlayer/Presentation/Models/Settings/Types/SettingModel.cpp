#include "SettingModel.hpp"
#include <QDebug>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)

SettingModel::SettingModel(Setting& setting, QObject* parent): QObject(parent), setting(setting) {
    connect(&setting, &Setting::valueChanged, this, &SettingModel::onValueChanged);
    connect(&setting, &Setting::isEnabledChanged, this, &SettingModel::onIsEnabledChanged);
}

QString SettingModel::getName() const {
    return setting.getName();
}

QString SettingModel::getToolTip() const {
    return setting.getToolTip();
}

QString SettingModel::getType() const {
    return setting.getType();
}

bool SettingModel::getEnabled() const {
    return setting.isEnabled();
}

void SettingModel::onIsEnabledChanged()
{
    emit enabledChanged();
}
