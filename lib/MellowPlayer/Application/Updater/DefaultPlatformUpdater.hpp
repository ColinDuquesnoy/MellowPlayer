#pragma once

#include "AbstractPlatformUpdater.hpp"

namespace MellowPlayer::Application {

    class DefaultPlatformUpdater: public AbstractPlatformUpdater
    {
    public:
        DefaultPlatformUpdater(IFileDownloader& downloader);
        virtual bool canInstall() const;

    protected:
        virtual void doInstall(const QString& assetFilePath) override;
        virtual QString getAssetUrl() const override;
        virtual QString getAssetFileName() const override;

    };

}