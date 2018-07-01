#pragma once

#include "MellowPlayer/Infrastructure/Helpers/Base64Helper.hpp"
#include <MellowPlayer/Domain/AlbumArt/IAlbumArtDownloader.hpp>
#include <MellowPlayer/Infrastructure/Network/FileDownloader.hpp>
#include <QFileInfo>

namespace MellowPlayer::Domain
{
    class ILogger;
}

namespace MellowPlayer::Infrastructure
{
    class AlbumArtDownloader : public Domain::IAlbumArtDownloader
    {
    public:
        AlbumArtDownloader();

        bool download(const QString& artUrl, const QString& songId) override;
        QFileInfo localArtUrl(const QString& songId) override;

    private slots:
        void onDownloadFinished(bool success);

    private:
        void downloadImage(const QString& url);
        bool isBase64Image(const QString& artUrl);
        bool createBase64Image(const QString base64String);

        FileDownloader fileDownloader_;
        QFileInfo localUrl_;
        Domain::ILogger& logger_;
        Base64Helper base64Helper_;
    };
}
