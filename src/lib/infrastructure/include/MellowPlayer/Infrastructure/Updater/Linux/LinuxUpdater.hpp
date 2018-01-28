#pragma once

#include <MellowPlayer/Infrastructure/Updater/AbstractPlatformUpdater.hpp>
#include <MellowPlayer/Infrastructure/Updater/Asset.hpp>

namespace MellowPlayer::Infrastructure
{
    class IFileDownloader;
    class Release;

    class LinuxUpdater : public AbstractPlatformUpdater
    {
    public:
        explicit LinuxUpdater(IFileDownloader& fileDownloader);

        void setRelease(const Release* release) override;
        bool canInstall() const override;
        void restart() override;

    protected:
        void doInstall(const QString& assetLocalPath) override;
        QString assetUrl() const override;
        QString assetFileName() const override;
        Asset asset_;
        QString destinationDir() const;
        QString destinationPath() const;
    };
}
