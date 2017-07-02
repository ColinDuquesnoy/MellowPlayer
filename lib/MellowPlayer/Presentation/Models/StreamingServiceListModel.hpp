#pragma once

#include <MellowPlayer/Presentation/ViewModels/StreamingServices/StreamingServiceViewModel.hpp>
#include "QQmlObjectListModel.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

using StreamingServiceListModel = QQmlObjectListModel<StreamingServiceViewModel>;

END_MELLOWPLAYER_NAMESPACE
