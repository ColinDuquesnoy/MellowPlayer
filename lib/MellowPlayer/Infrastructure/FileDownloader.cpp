#include "FileDownloader.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

FileDownloader::FileDownloader()
{
    connect(&networkAccessManager_, &QNetworkAccessManager::finished, this, &FileDownloader::onDownloadFinished);
}

void FileDownloader::download(const QString &urlToDownload, const QString &filePath)
{
    if (!isDownloading()) {
        progress_ = 0;
        destinationPath_ = QFileInfo(filePath);
        currentReply = networkAccessManager_.get(QNetworkRequest(QUrl(urlToDownload)));
        connect(currentReply, &QNetworkReply::downloadProgress, this, &FileDownloader::onDownloadProgress);
    }
}

double FileDownloader::getProgress() const
{
    return progress_;
}

bool FileDownloader::isDownloading() const
{
    return currentReply != nullptr;
}

void FileDownloader::onDownloadFinished(QNetworkReply *reply)
{
    bool success = false;

    currentReply = nullptr;

    if (reply->error() == QNetworkReply::NoError) {
        QString redirectUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toString();

        if (!redirectUrl.isEmpty()) {
            download(redirectUrl, destinationPath_.absoluteFilePath());
            return;
        }

        QByteArray replyData = reply->readAll();
        QFile file(destinationPath_.absoluteFilePath());
        if (file.open(QIODevice::WriteOnly)) {
            file.write(replyData);
            success = true;
        }
    }

    emit finished(success);
}

void FileDownloader::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{

    double ratio = 0;
    if (bytesTotal > bytesReceived)
        ratio = static_cast<double>(bytesReceived) / bytesTotal;
    double progress = (ratio * 100);

    if (progress_ != progress) {
        progress_ = progress;
        emit progressChanged();
    }
}
