#pragma once

#include "MellowPlayer/Infrastructure/Helpers/Base64Helper.hpp"
#include <MellowPlayer/Application/AlbumArt/IAlbumArtDownloader.hpp>
#include <MellowPlayer/Infrastructure/FileDownloader.hpp>
#include <QFileInfo>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

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
        QFileInfo getLocalArtUrl(const QString& songId) override;

    private slots:
        void onDownloadFinished(bool);

    private:
        void downloadImage(const QString& url);
        bool isBase64Image(const QString& artUrl);
        bool createBase64Image(const QString base64String);

        FileDownloader fileDownloader;
        QFileInfo localUrl;
        Application::ILogger& logger;
        Base64Helper base64;
    };
}
