#include <MellowPlayer/Application/Player/IPlayer.hpp>
#include <MellowPlayer/Application/Player/Song.hpp>
#include <MellowPlayer/Application/Utils/AlbumArt/IAlbumArtDownloader.hpp>
#include "LocalAlbumArt.hpp"

USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Application)
USING_MELLOWPLAYER_NAMESPACE(Infrastructure)


LocalAlbumArt::LocalAlbumArt(IPlayer& player, IAlbumArtDownloader& downloader): downloader(downloader) {
    connect(&player, &IPlayer::currentSongChanged, this, &LocalAlbumArt::onCurrentSongChanged);
    connect(&downloader, &IAlbumArtDownloader::downloadFinished, this, &LocalAlbumArt::onDownloadFinished);
}

const QString& LocalAlbumArt::getUrl() const {
    return url;
}

void LocalAlbumArt::onCurrentSongChanged(Song* song) {
    if (song != nullptr && !song->getArtUrl().isEmpty() && !song->getUniqueId().isEmpty())
        downloader.download(song->getArtUrl(), song->getUniqueId());
}

void LocalAlbumArt::onDownloadFinished(const QString& newUrl) {
    if(newUrl != url) {
        url = newUrl;
        emit urlChanged();
    }
}

bool LocalAlbumArt::isSongArtReady(const Song& song) {
    return url.contains(song.getUniqueId()) && QFileInfo(url).exists();
}
