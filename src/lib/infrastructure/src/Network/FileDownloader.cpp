#include <MellowPlayer/Infrastructure/Network/FileDownloader.hpp>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <MellowPlayer/Domain/Logging/ILogger.hpp>
#include <MellowPlayer/Domain/Logging/Loggers.hpp>
#include <MellowPlayer/Domain/Logging/LoggingMacros.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

FileDownloader::FileDownloader() : logger_(Loggers::logger("FileDownloader"))
{
    connect(&networkAccessManager_, &QNetworkAccessManager::finished, this, &FileDownloader::onDownloadFinished);
}

void FileDownloader::download(const QString& urlToDownload, const QString& filePath)
{
    if (!isDownloading()) {
        LOG_DEBUG(logger_, "downloading " << urlToDownload << " to " << filePath);
        progress_ = 0;
        destinationPath_ = QFileInfo(filePath);
        currentReply_ = networkAccessManager_.get(QNetworkRequest(QUrl(urlToDownload)));
        connect(currentReply_, &QNetworkReply::downloadProgress, this, &FileDownloader::onDownloadProgress);
    }
}

double FileDownloader::progress() const
{
    return progress_;
}

bool FileDownloader::isDownloading() const
{
    return currentReply_ != nullptr;
}

void FileDownloader::onDownloadFinished(QNetworkReply* reply)
{
    bool success = false;

    currentReply_ = nullptr;

    if (reply->error() == QNetworkReply::NoError) {
        QString redirectUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString();

        if (!redirectUrl.isEmpty()) {
            LOG_DEBUG(logger_, "redirected to: " << redirectUrl);
            download(redirectUrl, destinationPath_.absoluteFilePath());
            return;
        }

        QByteArray replyData = reply->readAll();
        QFile file(destinationPath_.absoluteFilePath());
        if (file.open(QIODevice::WriteOnly)) {
            file.write(replyData);

            LOG_DEBUG(logger_, "file downloaded with success: " << destinationPath_.absoluteFilePath());
            success = true;
        } else
            LOG_DEBUG(logger_, "failed to write file: " << destinationPath_.absoluteFilePath() << " - Error: " << file.errorString());
    } else
        LOG_DEBUG(logger_, "download failed: " << reply->errorString());

    emit finished(success);
}

void FileDownloader::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{

    double ratio = 0;
    if (bytesTotal > bytesReceived)
        ratio = static_cast<double>(bytesReceived) / bytesTotal;
    double progress = (ratio * 100);

    if (progress_ != progress) {
        LOG_DEBUG(logger_, "download progress: " << progress);
        progress_ = progress;
        emit progressChanged(progress_);
    }
}
