#pragma once

#include "Filter.hpp"
#include <memory>

namespace MellowPlayer::Infrastructure
{
    class IPlatformFilter;

    class PlatformFilterFactory
    {
    public:
        std::unique_ptr<IPlatformFilter> create(Filter filter) const;
    };
}
