#pragma once

#include <QFileInfo>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <MellowPlayer/UseCases/Interfaces/IAlbumArtDownloader.hpp>
#include "Base64Helper.hpp"

PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ILogger)

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class AlbumArtDownloader: public UseCases::IAlbumArtDownloader {
public:
    AlbumArtDownloader();

    bool download(const QString& artUrl, const QString& songId) override;
    QFileInfo getLocalArtUrl(const QString &songId) override;

private slots:
    void onDownloadFinished(QNetworkReply* reply);

private:
    bool isBase64Image(const QString& artUrl);
    bool createBase64Image(const QString base64String);

    QNetworkAccessManager *networkAccessManager;
    QFileInfo localUrl;
    UseCases::ILogger& logger;
    Base64Helper base64;

    void downloadImage(const QString& url) const;
};

END_MELLOWPLAYER_NAMESPACE
