#pragma once

#include "IPlatformFilter.hpp"

namespace MellowPlayer::Infrastructure
{
    class OsxFilter : public IPlatformFilter
    {
    public:
        bool match() const override;
    };
}
