#include "MellowPlayer/Presentation/Models/Settings/Types/SettingModel.hpp"
#include "SettingsModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Presentation)


SettingsModel::SettingsModel(Settings& settings, QObject* parent): QObject(parent), settings(settings) {

}

SettingModel* SettingsModel::get(int key) {
    SettingKey::Keys settingKey = static_cast<SettingKey::Keys>(key);
    Setting& setting = settings.get(settingKey);
    return settingModelFactory.create(setting, this);
}
