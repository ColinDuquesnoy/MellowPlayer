#pragma once

#include <MellowPlayer/Infrastructure/Network/IFileDownloader.hpp>

namespace MellowPlayer::Tests
{
    class FakeFileDownloader : public Infrastructure::IFileDownloader
    {
    public:
        void download(const QString&, const QString&){};
        double progress() const
        {
            return 0;
        };
        bool isDownloading() const
        {
            return false;
        };
    };
}