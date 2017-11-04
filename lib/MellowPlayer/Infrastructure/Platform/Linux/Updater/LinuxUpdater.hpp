#pragma once

#include <MellowPlayer/Domain/Updater/AbstractPlatformUpdater.hpp>
#include <MellowPlayer/Domain/Updater/Asset.hpp>

namespace MellowPlayer::Domain {
    class IFileDownloader;
    class Release;
}

namespace MellowPlayer::Infrastructure
{
    class LinuxUpdater : public Domain::AbstractPlatformUpdater
    {
    public:
        explicit LinuxUpdater(Domain::IFileDownloader& fileDownloader);

        void setRelease(const Domain::Release* release) override;
        bool canInstall() const override;
        void restart() override;

    protected:
        void doInstall(const QString& assetLocalPath) override;
        QString assetUrl() const override;
        QString assetFileName() const override;
        Domain::Asset asset_;
        QString destinationDir() const;
        QString destinationPath() const;
    };
}
