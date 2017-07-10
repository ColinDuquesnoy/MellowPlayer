#pragma once

#include <MellowPlayer/Presentation/ViewModels/ListeningHistory/ListeningHistoryEntryViewModel.hpp>
#include "QQmlObjectListModel.hpp"

namespace MellowPlayer::Presentation {

    using ListeningHistoryListModel = QQmlObjectListModel<ListeningHistoryEntryViewModel>;

}
