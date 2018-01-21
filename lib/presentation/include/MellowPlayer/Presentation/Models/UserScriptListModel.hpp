#pragma once

#include "QQmlObjectListModel.hpp"
#include <MellowPlayer/Presentation/ViewModels/UserScripts/UserScriptViewModel.hpp>

namespace MellowPlayer::Presentation
{
    using UserScriptListModel = QQmlObjectListModel<UserScriptViewModel>;
}
