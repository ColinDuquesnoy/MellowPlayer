#include "LocalAlbumArt.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)


LocalAlbumArt::LocalAlbumArt(IPlayer& player, IAlbumArtDownloader& downloader): downloader(downloader) {
    connect(&player, &IPlayer::currentSongChanged, this, &LocalAlbumArt::onCurrentSongChanged);
    connect(&downloader, &IAlbumArtDownloader::downloadFinished, this, &LocalAlbumArt::onDownloadFinished);
}

const QString& LocalAlbumArt::getUrl() const {
    return url;
}

void LocalAlbumArt::onCurrentSongChanged(Song* song) {
    if (song != nullptr)
        downloader.download(song->getArtUrl(), song->getUniqueId());
}

void LocalAlbumArt::onDownloadFinished(const QString& newUrl) {
    if(newUrl != url) {
        url = newUrl;
        emit urlChanged();
    }
}
