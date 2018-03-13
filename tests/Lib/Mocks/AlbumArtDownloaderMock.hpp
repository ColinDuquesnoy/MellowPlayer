#pragma once

#include <MellowPlayer/Domain/AlbumArt/IAlbumArtDownloader.hpp>
#include <fakeit/fakeit.hpp>

using namespace MellowPlayer::Domain;
using namespace fakeit;

#define LOCAL_URL "/path/to/art/songId"

class FakeAlbumArtDownloader : public IAlbumArtDownloader
{
public:
    bool download(const QString& artUrl, const QString& songId) override
    {
        _artUrl = artUrl;
        _localArtUrl = LOCAL_URL + songId;
        emit downloadFinished(_localArtUrl);
        return true;
    }

    QFileInfo localArtUrl(const QString&) override
    {
        return QFileInfo(_localArtUrl);
    }

    QString artUrl()
    {
        return _artUrl;
    }

    QString localArtUrl()
    {
        return _localArtUrl;
    }

private:
    QString _artUrl;
    QString _localArtUrl;
};
