#pragma once

#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsCategoryViewModel.hpp>
#include "QQmlObjectListModel.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

using SettingsCategoryListModel = QQmlObjectListModel<SettingsCategoryViewModel>;

END_MELLOWPLAYER_NAMESPACE
