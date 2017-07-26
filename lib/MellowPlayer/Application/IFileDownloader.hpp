#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>

namespace MellowPlayer::Application
{
    class IFileDownloader : public QObject
    {
        Q_OBJECT
    public:
        virtual ~IFileDownloader();

        virtual void download(const QString& urlToDownload, const QString& filePath) = 0;
        virtual double getProgress() const = 0;
        virtual bool isDownloading() const = 0;

    signals:
        void progressChanged(double progress);
        void finished(bool success);
    };
}
