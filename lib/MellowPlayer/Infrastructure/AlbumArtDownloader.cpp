#include <QStandardPaths>
#include <QDir>
#include "AlbumArtDownloader.hpp"

USE_MELLOWPLAYER_NAMESPACE(UseCases)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)

AlbumArtDownloader::AlbumArtDownloader()
    : networkAccessManager(new QNetworkAccessManager(this)),
      logger(LoggingManager::instance().getLogger("AlbumArtDownloader")) {

    connect(networkAccessManager, &QNetworkAccessManager::finished, this, &AlbumArtDownloader::onDownloadFinished);
}

bool AlbumArtDownloader::download(const QString& url, const QString& songId) {
    if (url.isEmpty() || songId.isEmpty())
        return false;

    artUrl = getLocalArtUrl(songId);
    LOG_DEBUG(logger, "downloading " + url + " to " + artUrl.absoluteFilePath());
    if (artUrl.exists()) {
        LOG_DEBUG(logger, "album art already exists locally")
        emit downloadFinished(artUrl.absoluteFilePath());
    } else {
        LOG_DEBUG(logger, "starting download");
        networkAccessManager->get(QNetworkRequest(url));
    }

    return true;
}

QFileInfo AlbumArtDownloader::getLocalArtUrl(const QString &songId) {
    auto cacheDir = QDir(QStandardPaths::standardLocations(QStandardPaths::CacheLocation)[0]);
    auto dir = QFileInfo(cacheDir, "Covers");
    auto dirPath = dir.absoluteFilePath();
    QDir(cacheDir).mkpath("Covers");
    QFileInfo localArtUrl = QFileInfo(dirPath, songId);
    return localArtUrl;
}

void AlbumArtDownloader::onDownloadFinished(QNetworkReply* reply) {
    LOG_DEBUG(logger, "download finished");
    QFile file(artUrl.absoluteFilePath());
    if (file.open(QIODevice::WriteOnly)) {
        file.write(reply->readAll());
        file.close();
    } else {
        LOG_DEBUG(logger, "could not open file in write only mode: " +artUrl.absoluteFilePath());
    }
    emit downloadFinished(artUrl.absoluteFilePath());
}
