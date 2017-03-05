#pragma once

#include "IService.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class IMprisService: public IService
{
public:
    virtual ~IMprisService() = default;
};

END_MELLOWPLAYER_NAMESPACE