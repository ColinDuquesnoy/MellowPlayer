#pragma once

#include <MellowPlayer/Application/IFileDownloader.hpp>

namespace MellowPlayer::Tests
{
    class FakeFileDownloader : public Application::IFileDownloader
    {
    public:
        void download(const QString&, const QString&){};
        double getProgress() const
        {
            return 0;
        };
        bool isDownloading() const
        {
            return false;
        };
    };
}