#pragma once

namespace MellowPlayer::Infrastructure
{
    class IHotkeys
    {
    public:
        virtual ~IHotkeys() = default;

        virtual void start() = 0;
        virtual void togglePlayPause() = 0;
        virtual void next() = 0;
        virtual void previous() = 0;
        virtual void toggleFavoriteSong() = 0;
        virtual void restoreWindow() = 0;
    };
}
