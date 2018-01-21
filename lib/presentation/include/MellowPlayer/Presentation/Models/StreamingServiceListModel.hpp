#pragma once

#include "QQmlObjectListModel.hpp"
#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServiceViewModel.hpp>

namespace MellowPlayer::Presentation
{
    using StreamingServiceListModel = QQmlObjectListModel<StreamingServiceViewModel>;
}
