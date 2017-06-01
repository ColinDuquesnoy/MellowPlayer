#pragma once

#include <MellowPlayer/Macros.hpp>

PREDECLARE_MELLOWPLAYER_STRUCT(Entities, Notification)

BEGIN_MELLOWPLAYER_NAMESPACE(Application)

class INotificationService {
public:
    virtual ~INotificationService() = default;
    virtual void initialize() = 0;
    virtual bool display(const Entities::Notification& notification) = 0;
};

END_MELLOWPLAYER_NAMESPACE