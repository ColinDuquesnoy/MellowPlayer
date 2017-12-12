#pragma once

#include <MellowPlayer/Infrastructure/Updater/AbstractPlatformUpdater.hpp>
#include <MellowPlayer/Infrastructure/Updater/Asset.hpp>

namespace MellowPlayer::Infrastructure
{
    class WindowsUpdater : public AbstractPlatformUpdater
    {
    public:
        explicit WindowsUpdater(IFileDownloader& fileDownloader);

        void setRelease(const Release* release) override;
        bool canInstall() const override;
        void restart() override;

    protected:
        void doInstall(const QString& assetLocalPath) override;
        QString assetUrl() const override;
        QString assetFileName() const override;
        Asset asset_;

    private:
        QString installerPath_;
    };
}
