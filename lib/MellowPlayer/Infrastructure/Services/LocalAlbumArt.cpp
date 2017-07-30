#include "LocalAlbumArt.hpp"
#include <MellowPlayer/Application/AlbumArt/IAlbumArtDownloader.hpp>
#include <MellowPlayer/Application/Player/IPlayer.hpp>
#include <MellowPlayer/Application/Player/Song.hpp>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

LocalAlbumArt::LocalAlbumArt(IPlayer& player, IAlbumArtDownloader& downloader) : downloader_(downloader)
{
    connect(&player, &IPlayer::currentSongChanged, this, &LocalAlbumArt::onCurrentSongChanged);
    connect(&downloader, &IAlbumArtDownloader::downloadFinished, this, &LocalAlbumArt::onDownloadFinished);
}

const QString& LocalAlbumArt::url() const
{
    return url_;
}

void LocalAlbumArt::onCurrentSongChanged(Song* song)
{
    if (song != nullptr && !song->artUrl().isEmpty() && !song->uniqueId().isEmpty())
        downloader_.download(song->artUrl(), song->uniqueId());
}

void LocalAlbumArt::onDownloadFinished(const QString& newUrl)
{
    if (newUrl != url_) {
        url_ = newUrl;
        emit urlChanged();
    }
}

bool LocalAlbumArt::isSongArtReady(const Song& song)
{
    return url_.contains(song.uniqueId()) && QFileInfo(url_).exists();
}
