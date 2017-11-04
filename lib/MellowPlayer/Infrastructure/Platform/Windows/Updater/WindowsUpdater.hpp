#pragma once

#include <MellowPlayer/Domain/Updater/AbstractPlatformUpdater.hpp>
#include <MellowPlayer/Domain/Updater/Asset.hpp>

namespace MellowPlayer::Infrastructure
{
    class WindowsUpdater : public Domain::AbstractPlatformUpdater
    {
    public:
        explicit WindowsUpdater(Domain::IFileDownloader& fileDownloader);

        void setRelease(const Domain::Release* release) override;
        bool canInstall() const override;
        void restart() override;

    protected:
        void doInstall(const QString& assetLocalPath) override;
        QString assetUrl() const override;
        QString assetFileName() const override;
        Domain::Asset asset_;

    private:
        QString installerPath_;
    };
}
