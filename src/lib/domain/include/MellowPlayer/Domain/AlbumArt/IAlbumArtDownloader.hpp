#pragma once

#include <QFileInfo>
#include <QObject>
#include <QString>

namespace MellowPlayer::Domain
{
    class IAlbumArtDownloader : public QObject
    {
        Q_OBJECT
    public:
        virtual ~IAlbumArtDownloader() = default;

        virtual bool download(const QString& artUrl, const QString& songId) = 0;
        virtual QFileInfo localArtUrl(const QString& songId) = 0;

    signals:
        void downloadFinished(const QString& localUrl);
        void downloadFailed();
    };
}
