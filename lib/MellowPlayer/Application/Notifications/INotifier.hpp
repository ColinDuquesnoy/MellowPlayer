#pragma once

#include <MellowPlayer/Macros.hpp>

PREDECLARE_MELLOWPLAYER_STRUCT(Application, Notification)

BEGIN_MELLOWPLAYER_NAMESPACE(Application)

class INotifier {
public:
    virtual ~INotifier() = default;
    virtual void initialize() = 0;
    virtual bool display(const Application::Notification& notification) = 0;
};

END_MELLOWPLAYER_NAMESPACE