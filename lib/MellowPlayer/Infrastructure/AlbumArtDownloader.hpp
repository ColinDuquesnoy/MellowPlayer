#pragma once

#include <QFileInfo>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <MellowPlayer/Logging.hpp>
#include <MellowPlayer/UseCases/IAlbumArtDownloader.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(Infrastructure)

class AlbumArtDownloader: public UseCases::IAlbumArtDownloader {
public:
    AlbumArtDownloader(Logging::LoggingManager& loggingManager, QObject* parent= nullptr);

    void download(const QString& artUrl, const QString& songId) override;

private slots:
    void onDownloadFinished(QNetworkReply* reply);

private:
    QFileInfo getLocalArtUrl(const QString &songId);
    QNetworkAccessManager *networkAccessManager;
    QFileInfo artUrl;
    Logging::ILogger& logger;
};

END_MELLOWPLAYER_NAMESPACE
