#pragma once

#include <MellowPlayer/Infrastructure/Updater/AbstractPlatformUpdater.hpp>
#include <MellowPlayer/Infrastructure/Updater/Asset.hpp>

namespace MellowPlayer::Infrastructure
{
    class OSXUpdater : public AbstractPlatformUpdater
    {
    public:
        explicit OSXUpdater(IFileDownloader& fileDownloader);

        void setRelease(const Release* release) override;
        bool canInstall() const override;
        void restart() override;

    protected:
        void doInstall(const QString& assetLocalPath) override;
        QString assetUrl() const override;
        QString assetFileName() const override;
        Asset asset_;

    private:
        QString dmgPath_;
    };
}
