#pragma once

#include "IPlatformFilter.hpp"

namespace MellowPlayer::Infrastructure
{
    class WindowsFilter : public IPlatformFilter
    {
    public:
        bool match() const override;
    };
}
