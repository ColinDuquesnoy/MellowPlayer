#pragma once

#include "LinuxFilterBase.hpp"

namespace MellowPlayer::Infrastructure
{
    class LinuxFilter: public LinuxFilterBase
    {
    public:
        bool match() const override;
    };
}
