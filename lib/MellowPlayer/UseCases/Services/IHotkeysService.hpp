#pragma once

#include "IService.hpp"

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class IHotkeysService: public IService
{
public:
    virtual ~IHotkeysService() = default;

    virtual void togglePlayPause() = 0;
    virtual void next() = 0;
    virtual void previous() = 0;
    virtual void toggleFavoriteSong() = 0;
};

END_MELLOWPLAYER_NAMESPACE