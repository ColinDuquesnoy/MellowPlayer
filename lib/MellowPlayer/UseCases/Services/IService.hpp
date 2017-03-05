#pragma once

#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class IService
{
public:
    virtual ~IService() = default;

    virtual bool start() = 0;
};

END_MELLOWPLAYER_NAMESPACE