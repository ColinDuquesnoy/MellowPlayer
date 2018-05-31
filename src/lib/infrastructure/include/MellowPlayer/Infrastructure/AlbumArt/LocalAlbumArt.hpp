#pragma once

#include <MellowPlayer/Domain/AlbumArt/ILocalAlbumArt.hpp>
#include <QTimer>

namespace MellowPlayer::Domain
{
    class Song;
    class IPlayer;
    class IAlbumArtDownloader;
}

namespace MellowPlayer::Infrastructure
{
    class LocalAlbumArt : public Domain::ILocalAlbumArt
    {
        Q_OBJECT
    public:
        LocalAlbumArt(Domain::IPlayer& player, Domain::IAlbumArtDownloader& downloader, int timeout=5000);

        const QString& url() const override;
        bool isReady(const Domain::Song& song) override;

        QString fallbackUrl() const;

    private slots:
        void onCurrentSongChanged(Domain::Song* song);
        void onDownloadFinished(const QString& newUrl);
        void onArtUrlChanged();

    private:
        Domain::IPlayer& _player;
        Domain::IAlbumArtDownloader& _downloader;
        QString _url;
        int _timeout;
        QTimer _timer;
    };
}
