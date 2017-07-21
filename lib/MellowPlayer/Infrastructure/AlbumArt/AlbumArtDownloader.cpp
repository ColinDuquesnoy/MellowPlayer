#include "AlbumArtDownloader.hpp"
#include <MellowPlayer/Application/Logging/LoggingManager.hpp>
#include <QDir>
#include <QImage>
#include <QStandardPaths>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

AlbumArtDownloader::AlbumArtDownloader() : logger(LoggingManager::instance().getLogger("AlbumArtDownloader"))
{

    connect(&fileDownloader, &FileDownloader::finished, this, &AlbumArtDownloader::onDownloadFinished);
}

bool AlbumArtDownloader::download(const QString &url, const QString &songId)
{
    if (url.isEmpty() || songId.isEmpty())
        return false;

    localUrl = getLocalArtUrl(songId);

    if (localUrl.exists()) {
        LOG_DEBUG(logger, "album art already exists locally")
        emit downloadFinished(localUrl.absoluteFilePath());
        return true;
    }

    if (isBase64Image(url))
        return createBase64Image(url);

    downloadImage(url);
    return true;
}

void AlbumArtDownloader::downloadImage(const QString &url)
{
    LOG_DEBUG(logger, "downloading " + url + " to " + localUrl.absoluteFilePath());
    fileDownloader.download(url, localUrl.absoluteFilePath());
}

QFileInfo AlbumArtDownloader::getLocalArtUrl(const QString &songId)
{
    auto cacheDir = QDir(QStandardPaths::standardLocations(QStandardPaths::CacheLocation)[0]);
    auto dir = QFileInfo(cacheDir, "Covers");
    auto dirPath = dir.absoluteFilePath();
    QDir(cacheDir).mkpath("Covers");
    QFileInfo localArtUrl = QFileInfo(dirPath, songId);
    return localArtUrl;
}

void AlbumArtDownloader::onDownloadFinished(bool)
{
    LOG_DEBUG(logger, "download finished");
    emit downloadFinished(localUrl.absoluteFilePath());
}

bool AlbumArtDownloader::isBase64Image(const QString &artUrl)
{
    return base64.isBase64(artUrl);
}

bool AlbumArtDownloader::createBase64Image(const QString base64String)
{
    LOG_DEBUG(logger, "creating base64 image from " + base64String + " to " + localUrl.absoluteFilePath());
    return base64.saveToFile(base64String, localUrl.absoluteFilePath());
}
