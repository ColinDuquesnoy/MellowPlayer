#include <MellowPlayer/Application/Settings/Setting.hpp>
#include "SettingModelFactory.hpp"
#include "Types/BoolSettingModel.hpp"
#include "Types/ColorSettingModel.hpp"
#include "Types/EnumSettingModel.hpp"
#include "Types/ShortcutSettingModel.hpp"
#include "Types/StringSettingModel.hpp"

USING_MELLOWPLAYER_NAMESPACE(Presentation)
USING_MELLOWPLAYER_NAMESPACE(Application)

SettingModel* SettingModelFactory::create(Setting& setting, QObject* parent) const {
    QString type = setting.getType().toLower();
    if (type == "bool") {
        return new BoolSettingModel(setting, parent);
    }
    else if (type == "color") {
        return new ColorSettingModel(setting, parent);
    }
    else if (type == "shortcut") {
        return new ShortcutSettingModel(setting, parent);
    }
    else if (type.startsWith("enum")) {
        return new EnumSettingModel(setting, parent);
    }
    return new StringSettingModel(setting, parent);
}
