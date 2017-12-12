#pragma once

#include "IPlatformFilter.hpp"

namespace MellowPlayer::Infrastructure
{
    class AllFilter: public IPlatformFilter
    {
    public:
        bool match() const override;
    };
}
