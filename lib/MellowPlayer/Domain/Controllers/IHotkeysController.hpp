#pragma once

namespace MellowPlayer::Domain
{
    class IHotkeysController
    {
    public:
        virtual ~IHotkeysController() = default;

        virtual void start() = 0;
        virtual void togglePlayPause() = 0;
        virtual void next() = 0;
        virtual void previous() = 0;
        virtual void toggleFavoriteSong() = 0;
        virtual void restoreWindow() = 0;
    };
}
