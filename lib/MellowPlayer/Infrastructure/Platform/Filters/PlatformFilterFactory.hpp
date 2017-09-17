#pragma once

#include "Filter.hpp"

namespace MellowPlayer::Infrastructure
{
    class IPlatformFilter;

    class IPlatformFilterFactory
    {
    public:
        virtual std::unique_ptr<IPlatformFilter> create(Filter filter) const = 0;
    };

    class PlatformFilterFactory: public IPlatformFilterFactory
    {
    public:
        std::unique_ptr<IPlatformFilter> create(Filter filter) const override;
    };
}
