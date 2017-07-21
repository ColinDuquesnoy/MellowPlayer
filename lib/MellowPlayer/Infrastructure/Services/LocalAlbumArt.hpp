#pragma once

#include <MellowPlayer/Application/AlbumArt/ILocalAlbumArt.hpp>

namespace MellowPlayer::Application
{
    class Song;
    class IPlayer;
    class IAlbumArtDownloader;
}

namespace MellowPlayer::Infrastructure
{
    class LocalAlbumArt : public Application::ILocalAlbumArt
    {
        Q_OBJECT
    public:
        LocalAlbumArt(Application::IPlayer &player, Application::IAlbumArtDownloader &downloader);

        const QString &getUrl() const override;
        bool isSongArtReady(const Application::Song &song) override;

    private slots:
        void onCurrentSongChanged(Application::Song *song);
        void onDownloadFinished(const QString &newUrl);

    private:
        Application::IAlbumArtDownloader &downloader;
        QString url;
    };
}
