#pragma once

namespace MellowPlayer::Presentation
{
    class IHotkeys
    {
    public:
        virtual ~IHotkeys() = default;

        virtual void initialize() = 0;
        virtual void togglePlayPause() = 0;
        virtual void next() = 0;
        virtual void previous() = 0;
        virtual void toggleFavoriteSong() = 0;
        virtual void restoreWindow() = 0;
    };
}
