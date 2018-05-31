#include <MellowPlayer/Infrastructure/AlbumArt/LocalAlbumArt.hpp>
#include <MellowPlayer/Domain/AlbumArt/IAlbumArtDownloader.hpp>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <MellowPlayer/Domain/Player/Song.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

LocalAlbumArt::LocalAlbumArt(IPlayer& player, IAlbumArtDownloader& downloader, int timeout)
        : _player(player),
          _downloader(downloader),
          _timeout(timeout)
{
    _timer.setInterval(timeout);
    _timer.setSingleShot(true);

    connect(&_timer, &QTimer::timeout, [&]() {
        if (_player.currentSong() != nullptr)
            _downloader.download(fallbackUrl(), _player.currentSong()->uniqueId());
    });

    connect(&player, &IPlayer::currentSongChanged, this, &LocalAlbumArt::onCurrentSongChanged);
    connect(&downloader, &IAlbumArtDownloader::downloadFinished, this, &LocalAlbumArt::onDownloadFinished);
}

const QString& LocalAlbumArt::url() const
{
    return _url;
}

void LocalAlbumArt::onCurrentSongChanged(Song* song)
{
    if (song != nullptr && !song->uniqueId().isEmpty()) {
        auto artUrl = song->artUrl();
        auto songId = song->uniqueId();

        if (song->artUrl().isEmpty()) {
            connect(song, &Song::artUrlChanged, this, &LocalAlbumArt::onArtUrlChanged);
            _timer.start();
        }
        else
            _downloader.download(artUrl, songId);
    }
}

void LocalAlbumArt::onDownloadFinished(const QString& newUrl)
{
    _timer.stop();
    if (newUrl != _url) {
        _url = newUrl;
        emit urlChanged();
    }
}

bool LocalAlbumArt::isReady(const Song& song)
{
    return _url.contains(song.uniqueId()) && QFileInfo(_url).exists();
}

QString LocalAlbumArt::fallbackUrl() const
{
    return "https://github.com/ColinDuquesnoy/MellowPlayer/blob/develop/src/lib/presentation/resources/icons/mellowplayer.png";
}

void LocalAlbumArt::onArtUrlChanged()
{
    Song* song = _player.currentSong();
    _downloader.download(song->artUrl(), song->uniqueId());
}
