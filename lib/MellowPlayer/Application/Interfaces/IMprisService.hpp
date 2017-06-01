#pragma once


BEGIN_MELLOWPLAYER_NAMESPACE(Application)

class IMprisService
{
public:
    virtual ~IMprisService() = default;
    virtual bool start() = 0;
};

END_MELLOWPLAYER_NAMESPACE