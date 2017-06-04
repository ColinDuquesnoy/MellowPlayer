#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/Application/Utils/AlbumArt/ILocalAlbumArt.hpp>

USE_MELLOWPLAYER_NAMESPACE(Application)
using namespace fakeit;

class LocalAlbumArtMock {
public:
    static Mock<ILocalAlbumArt> getMockWithUrlNotOk() {
        Mock<ILocalAlbumArt> mock;
        When(Method(mock, getUrl)).AlwaysReturn("/tmp/songId");
        When(Method(mock, isSongArtReady)).AlwaysReturn(false);
        return mock;
    }
    static Mock<ILocalAlbumArt> getMockWithUrlOk() {
        Mock<ILocalAlbumArt> mock;
        When(Method(mock, getUrl)).AlwaysReturn("/tmp/songId");
        When(Method(mock, isSongArtReady)).AlwaysReturn(true);
        return mock;
    }
};
