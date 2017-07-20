#pragma once

#include <QtCore/QFileInfo>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <MellowPlayer/Application/IFileDownloader.hpp>

namespace MellowPlayer::Infrastructure {

    class FileDownloader: public Application::IFileDownloader
    {
        Q_OBJECT
    public:
        FileDownloader();

        void download(const QString& urlToDownload, const QString& filePath) override;
        double getProgress() const override;
        bool isDownloading() const override;

    private slots:
        void onDownloadFinished(QNetworkReply* reply);
        void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

    private:
        QNetworkAccessManager networkAccessManager_;
        QFileInfo destinationPath_;
        QNetworkReply* currentReply = nullptr;
        double progress_ = 0;
    };
}
