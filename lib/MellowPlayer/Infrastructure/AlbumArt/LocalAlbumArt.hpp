#pragma once

#include <MellowPlayer/Domain/AlbumArt/ILocalAlbumArt.hpp>

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
        LocalAlbumArt(Domain::IPlayer& player, Domain::IAlbumArtDownloader& downloader);

        const QString& url() const override;
        bool isSongArtReady(const Domain::Song& song) override;

    private slots:
        void onCurrentSongChanged(Domain::Song* song);
        void onDownloadFinished(const QString& newUrl);
        void onArtUrlChanged();

    private:
        Domain::IPlayer& player_;
        Domain::IAlbumArtDownloader& downloader_;
        QString url_;
    };
}
