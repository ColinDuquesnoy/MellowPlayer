#include <MellowPlayer/Application/Player/IPlayer.hpp>
#include <MellowPlayer/Entities/Song.hpp>
#include <MellowPlayer/Application/Interfaces/IAlbumArtDownloader.hpp>
#include "LocalAlbumArtService.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(Application)
USE_MELLOWPLAYER_NAMESPACE(Infrastructure)


LocalAlbumArtService::LocalAlbumArtService(IPlayer& player, IAlbumArtDownloader& downloader): downloader(downloader) {
    connect(&player, &IPlayer::currentSongChanged, this, &LocalAlbumArtService::onCurrentSongChanged);
    connect(&downloader, &IAlbumArtDownloader::downloadFinished, this, &LocalAlbumArtService::onDownloadFinished);
}

const QString& LocalAlbumArtService::getUrl() const {
    return url;
}

void LocalAlbumArtService::onCurrentSongChanged(Song* song) {
    if (song != nullptr && !song->getArtUrl().isEmpty() && !song->getUniqueId().isEmpty())
        downloader.download(song->getArtUrl(), song->getUniqueId());
}

void LocalAlbumArtService::onDownloadFinished(const QString& newUrl) {
    if(newUrl != url) {
        url = newUrl;
        emit urlChanged();
    }
}

bool LocalAlbumArtService::isSongArtReady(const Song& song) {
    return url.contains(song.getUniqueId()) && QFileInfo(url).exists();
}
