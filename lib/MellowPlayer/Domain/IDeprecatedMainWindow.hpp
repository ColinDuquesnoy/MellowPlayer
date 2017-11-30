#pragma once

namespace MellowPlayer::Domain
{
    class IDeprecatedMainWindow
    {
    public:
        virtual ~IDeprecatedMainWindow() = default;

        virtual bool load() = 0;
        virtual void show() = 0;
        virtual void hide() = 0;
    };
}
