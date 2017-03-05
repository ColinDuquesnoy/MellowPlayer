#pragma once

#include <fakeit.hpp>
#include <MellowPlayer/UseCases.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace fakeit;

#define LOCAL_URL "/path/to/art"

class AlbumArtDownloaderMock: public IAlbumArtDownloader {
public:
    bool download(const QString&, const QString&) {
        emit downloadFinished(LOCAL_URL);
        return true;
    }
};



