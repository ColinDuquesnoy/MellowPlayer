#pragma once


BEGIN_MELLOWPLAYER_NAMESPACE(Application)

class IMprisController
{
public:
    virtual ~IMprisController() = default;
    virtual bool start() = 0;
};

END_MELLOWPLAYER_NAMESPACE