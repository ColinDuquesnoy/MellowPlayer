#include <QStandardPaths>
#include <QDir>
#include "AlbumArtDownloader.hpp"

USE_MELLOWPLAYER_NAMESPACE(Logging)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

AlbumArtDownloader::AlbumArtDownloader(LoggingManager& loggingManager, QObject* parent)
    : IAlbumArtDownloader(parent), networkAccessManager(new QNetworkAccessManager(this)),
      logger(loggingManager.getLogger("AlbumArtDownloader")) {

    connect(networkAccessManager, &QNetworkAccessManager::finished, this, &AlbumArtDownloader::onDownloadFinished);
}

void AlbumArtDownloader::download(const QString& url, const QString& songId) {
    artUrl = getLocalArtUrl(songId);
    LOG_INFO(logger, "downloading " << url << " to " << artUrl.absoluteFilePath());
    if (artUrl.exists()) {
        LOG_DEBUG(logger, "album art already exists locally")
        emit downloadFinished(artUrl.absoluteFilePath());
    } else {
        LOG_DEBUG(logger, "starting download");
        networkAccessManager->get(QNetworkRequest(url));
    }
}

QFileInfo AlbumArtDownloader::getLocalArtUrl(const QString &songId) {
    if (songId.isEmpty())
        return QFileInfo();

    auto cacheDir = QDir(QStandardPaths::standardLocations(QStandardPaths::CacheLocation)[0]);
    auto dir = QFileInfo(cacheDir, "Covers");
    auto dirPath = dir.absoluteFilePath();
    if (!dir.exists()) {
        QDir(cacheDir).mkdir("Covers");
    }
    QFileInfo localArtUrl = QFileInfo(dirPath, songId);
    return localArtUrl;
}

void AlbumArtDownloader::onDownloadFinished(QNetworkReply* reply) {
    LOG_DEBUG(logger, "download finished");
    QFile file(artUrl.absoluteFilePath());
    if (file.open(QIODevice::WriteOnly)) {
        file.write(reply->readAll());
        file.close();
    }
    emit downloadFinished(artUrl.absoluteFilePath());
}
