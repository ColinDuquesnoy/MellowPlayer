#pragma once

#include "MellowPlayer/Infrastructure/Helpers/Base64Helper.hpp"
#include <MellowPlayer/Application/AlbumArt/IAlbumArtDownloader.hpp>
#include <MellowPlayer/Infrastructure/FileDownloader.hpp>
#include <QFileInfo>

namespace MellowPlayer::Application
{
    class ILogger;
}

namespace MellowPlayer::Infrastructure
{
    class AlbumArtDownloader : public Application::IAlbumArtDownloader
    {
    public:
        AlbumArtDownloader();

        bool download(const QString& artUrl, const QString& songId) override;
        QFileInfo localArtUrl(const QString& songId) override;

    private slots:
        void onDownloadFinished(bool);

    private:
        void downloadImage(const QString& url);
        bool isBase64Image(const QString& artUrl);
        bool createBase64Image(const QString base64String);

        FileDownloader fileDownloader_;
        QFileInfo localUrl_;
        Application::ILogger& logger_;
        Base64Helper base64Helper_;
    };
}
