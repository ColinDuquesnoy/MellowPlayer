#pragma once

#include "QQmlObjectListModel.hpp"
#include <MellowPlayer/Presentation/ViewModels/Settings/SettingsCategoryViewModel.hpp>

namespace MellowPlayer::Presentation
{
    using SettingsCategoryListModel = QQmlObjectListModel<SettingsCategoryViewModel>;
}
