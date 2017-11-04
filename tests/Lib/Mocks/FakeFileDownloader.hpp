#pragma once

#include <MellowPlayer/Domain/IFileDownloader.hpp>

namespace MellowPlayer::Tests
{
    class FakeFileDownloader : public Domain::IFileDownloader
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