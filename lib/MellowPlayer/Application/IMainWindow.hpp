#pragma once

namespace MellowPlayer::Application
{
    class IMainWindow
    {
    public:
        virtual ~IMainWindow() = default;

        virtual bool load() = 0;
        virtual void show() = 0;
        virtual void hide() = 0;
    };
}
