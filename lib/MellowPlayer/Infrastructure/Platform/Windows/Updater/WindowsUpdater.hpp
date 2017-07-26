#pragma once

#include <MellowPlayer/Application/Updater/AbstractPlatformUpdater.hpp>
#include <MellowPlayer/Application/Updater/Asset.hpp>

namespace MellowPlayer::Infrastructure
{
    class WindowsUpdater : public Application::AbstractPlatformUpdater
    {
    public:
        explicit WindowsUpdater(Application::IFileDownloader& fileDownloader);

        void setRelease(const Application::Release* release) override;
        bool canInstall() const override;
        void restart() override;

    protected:
        void doInstall(const QString& assetLocalPath) override;
        QString getAssetUrl() const override;
        QString getAssetFileName() const override;
        Application::Asset asset_;

    private:
        QString installerPath_;
    };
}
