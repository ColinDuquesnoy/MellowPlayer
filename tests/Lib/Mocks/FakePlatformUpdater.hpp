#pragma once

#include <MellowPlayer/Domain/Updater/AbstractPlatformUpdater.hpp>

namespace MellowPlayer::Tests
{
    class FakePlatformUpdater : public Domain::AbstractPlatformUpdater
    {
    public:
        FakePlatformUpdater(Domain::IFileDownloader& fileDownloader) : Domain::AbstractPlatformUpdater(fileDownloader)
        {
        }

        bool canInstall() const override
        {
            return canInstall_;
        }

        void setCanInstall(bool enable)
        {
            canInstall_ = enable;
        }

        void finishDownload()
        {
            emit downloadFinished(true);
        }

        void finishInstall()
        {
            emit installFinished(true);
        }

    protected:
        void doInstall(const QString&) override
        {
        }

        QString assetUrl() const override
        {
            return nullptr;
        }

        QString assetFileName() const override
        {
            return nullptr;
        }

    private:
        bool canInstall_ = false;
    };
}