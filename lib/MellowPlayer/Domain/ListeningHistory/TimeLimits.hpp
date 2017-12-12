#pragma once

namespace MellowPlayer::Domain
{
    enum class TimeLimits
    {
        Today = 0,
        Yesterday = 1,
        LastWeek = 2,
        LastMonth = 3,
        LastYear = 4,
        Never = 5,
    };
}
