#pragma once

#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryEntryViewModel.hpp>
#include "QQmlObjectListModel.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

using ListeningHistoryListModel = QQmlObjectListModel<ListeningHistoryEntryViewModel>;

END_MELLOWPLAYER_NAMESPACE
