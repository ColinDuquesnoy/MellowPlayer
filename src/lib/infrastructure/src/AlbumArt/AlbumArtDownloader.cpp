#include <MellowPlayer/Infrastructure/AlbumArt/AlbumArtDownloader.hpp>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>
#include <QDir>
#include <QStandardPaths>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

AlbumArtDownloader::AlbumArtDownloader() : logger_(Loggers::logger("AlbumArtDownloader"))
{

    connect(&fileDownloader_, &FileDownloader::finished, this, &AlbumArtDownloader::onDownloadFinished);
}

bool AlbumArtDownloader::download(const QString& url, const QString& songId)
{
    if (url.isEmpty() || songId.isEmpty())
        return false;

    localUrl_ = localArtUrl(songId);

    if (localUrl_.exists()) {
        LOG_DEBUG(logger_, "album art already exists locally")
        emit downloadFinished(localUrl_.absoluteFilePath());
        return true;
    }

    if (isBase64Image(url))
        return createBase64Image(url);

    downloadImage(url);
    return true;
}

void AlbumArtDownloader::downloadImage(const QString& url)
{
    LOG_DEBUG(logger_, "downloading " + url + " to " + localUrl_.absoluteFilePath());
    fileDownloader_.download(url, localUrl_.absoluteFilePath());
}

QFileInfo AlbumArtDownloader::localArtUrl(const QString& songId)
{
    auto cacheDir = QDir(QStandardPaths::standardLocations(QStandardPaths::CacheLocation)[0]);
    auto dir = QFileInfo(cacheDir, "Covers");
    auto dirPath = dir.absoluteFilePath();
    QDir(cacheDir).mkpath("Covers");
    QFileInfo localArtUrl = QFileInfo(dirPath, songId);
    return localArtUrl;
}

void AlbumArtDownloader::onDownloadFinished(bool success)
{
    LOG_DEBUG(logger_, "download finished");
    if (success)
        emit downloadFinished(localUrl_.absoluteFilePath());
    else
        emit downloadFailed();
}

bool AlbumArtDownloader::isBase64Image(const QString& artUrl)
{
    return base64Helper_.isBase64(artUrl);
}

bool AlbumArtDownloader::createBase64Image(const QString base64String)
{
    LOG_DEBUG(logger_, "creating base64 image from " + base64String + " to " + localUrl_.absoluteFilePath());
    bool retVal = base64Helper_.saveToFile(base64String, localUrl_.absoluteFilePath());
    if (retVal)
        emit downloadFinished(localUrl_.absoluteFilePath());
    return retVal;
}
