#pragma once


BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class IMprisService
{
public:
    virtual ~IMprisService() = default;
    virtual bool start() = 0;
};

END_MELLOWPLAYER_NAMESPACE