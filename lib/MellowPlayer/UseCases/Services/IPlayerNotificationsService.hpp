#pragma once

#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class INotificationService {
public:
    virtual ~INotificationService() = default;
    virtual void initialize() = 0;
    virtual void display(const Notification& notification) = 0;
};

END_MELLOWPLAYER_NAMESPACE