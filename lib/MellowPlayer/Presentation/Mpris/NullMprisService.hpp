#pragma once

#include "IMprisService.hpp"

namespace MellowPlayer::Presentation
{
    class NullMprisService: public IMprisService
    {
    public:
        virtual bool start();
    };
}
