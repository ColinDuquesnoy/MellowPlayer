#pragma once

#include "IPlatformFilter.hpp"

namespace MellowPlayer::Infrastructure
{
    class LinuxFilterBase: public IPlatformFilter
    {
    public:
        LinuxFilterBase();

    protected:
        bool isAppImage_;
    };
}
