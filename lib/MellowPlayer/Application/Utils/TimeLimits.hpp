#pragma once

#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Application)

enum class TimeLimits {
    Today = 0,
    Yesterday = 1,
    LastWeek = 2,
    LastMonth = 3,
    LastYear = 4,
    Never = 5
};

END_MELLOWPLAYER_NAMESPACE
