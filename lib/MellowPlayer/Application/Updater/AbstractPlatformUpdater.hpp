#pragma once

#include "IHttpClient.hpp"
#include <QtCore/QString>

namespace MellowPlayer::Application
{
    class Release;
    class IFileDownloader;

    class AbstractPlatformUpdater : public QObject
    {
        Q_OBJECT
    public:
        AbstractPlatformUpdater(IFileDownloader &fileDownloader);

        void setRelease(const Release *release);
        void download();
        void install();

        virtual bool canInstall() const = 0;

    signals:
        void downloadFinished(bool success);
        void installFinished(bool success);

    protected:
        virtual void doInstall(const QString &assetFilePath) = 0;
        virtual QString getAssetUrl() const = 0;
        virtual QString getAssetFileName() const = 0;

        const Release *release_ = nullptr;

    private:
        QString makeDestinationPath();

        QString assetFilePath_;
        IFileDownloader &fileDownloader_;
    };
}
