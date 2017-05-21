#include <MellowPlayer/UseCases/Settings/Setting.hpp>
#include "SettingModelFactory.hpp"
#include "Types/BoolSettingModel.hpp"
#include "Types/StringSettingModel.hpp"

USE_MELLOWPLAYER_NAMESPACE(Presentation)
USE_MELLOWPLAYER_NAMESPACE(UseCases)

SettingModel* SettingModelFactory::create(Setting& setting, QObject* parent) {
    if (setting.getType() == "bool") {
        return new BoolSettingModel(setting, parent);
    }
    return new StringSettingModel(setting, parent);
}
