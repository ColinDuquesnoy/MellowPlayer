#pragma once

#include <MellowPlayer/UseCases.hpp>
#include "GenericListModel.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(Presentation)

using StreamingServicesModel = GenericListModel<UseCases::StreamingService>;

END_MELLOWPLAYER_NAMESPACE