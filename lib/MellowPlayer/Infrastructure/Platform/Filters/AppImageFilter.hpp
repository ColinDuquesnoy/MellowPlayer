#pragma once

#include "LinuxFilterBase.hpp"

namespace MellowPlayer::Infrastructure
{
    class AppImageFilter: public LinuxFilterBase
    {
    public:
        bool match() const override;
    };
}
