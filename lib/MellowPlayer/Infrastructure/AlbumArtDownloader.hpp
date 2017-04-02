#pragma once

#include <QFileInfo>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <MellowPlayer/UseCases/Interfaces/IAlbumArtDownloader.hpp>

PREDECLARE_MELLOWPLAYER_CLASS(UseCases, ILogger)

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class AlbumArtDownloader: public UseCases::IAlbumArtDownloader {
public:
    AlbumArtDownloader();

    bool download(const QString& artUrl, const QString& songId) override;
    QFileInfo getLocalArtUrl(const QString &songId);

private slots:
    void onDownloadFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager *networkAccessManager;
    QFileInfo artUrl;
    UseCases::ILogger& logger;
};

END_MELLOWPLAYER_NAMESPACE
