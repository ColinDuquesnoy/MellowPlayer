#pragma once

#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

struct Notification;

class INotificationPresenter
{
public:
    virtual ~INotificationPresenter() = default;
    virtual void initialize() = 0;
    virtual bool display(const Notification& notification) = 0;
};

END_MELLOWPLAYER_NAMESPACE
