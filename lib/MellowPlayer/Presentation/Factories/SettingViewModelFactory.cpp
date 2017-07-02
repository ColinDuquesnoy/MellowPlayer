#include <MellowPlayer/Application/Settings/Setting.hpp>
#include "SettingViewModelFactory.hpp"
#include "MellowPlayer/Presentation/ViewModels/Settings/Types/BoolSettingViewModel.hpp"
#include "MellowPlayer/Presentation/ViewModels/Settings/Types/ColorSettingViewModel.hpp"
#include "MellowPlayer/Presentation/ViewModels/Settings/Types/EnumSettingViewModel.hpp"
#include "MellowPlayer/Presentation/ViewModels/Settings/Types/ShortcutSettingViewModel.hpp"
#include "MellowPlayer/Presentation/ViewModels/Settings/Types/TimeLimitSettingViewModel.hpp"
#include "MellowPlayer/Presentation/ViewModels/Settings/Types/StringSettingViewModel.hpp"

USING_MELLOWPLAYER_NAMESPACE(Presentation)
USING_MELLOWPLAYER_NAMESPACE(Application)

SettingViewModel* SettingViewModelFactory::create(Setting& setting, QObject* parent) const {
    QString type = setting.getType().toLower();
    if (type == "bool") {
        return new BoolSettingViewModel(setting, parent);
    }
    else if (type == "color") {
        return new ColorSettingViewModel(setting, parent);
    }
    else if (type == "shortcut") {
        return new ShortcutSettingViewModel(setting, parent);
    }
    else if (type.startsWith("enum")) {
        return new EnumSettingViewModel(setting, parent);
    } else if (type.startsWith("time-limit")) {
        return new TimeLimitSettingViewModel(setting, parent);
    }
    return new StringSettingViewModel(setting, parent);
}
