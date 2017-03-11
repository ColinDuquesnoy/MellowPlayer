#pragma once

#include <QString>
#include <MellowPlayer/Macros.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class ISystemTrayIcon
{
public:
    virtual ~ISystemTrayIcon() = default;

    virtual void show() = 0;
    virtual void hide() = 0;
    virtual void showMessage(const QString& title, const QString& message) = 0;
};

END_MELLOWPLAYER_NAMESPACE