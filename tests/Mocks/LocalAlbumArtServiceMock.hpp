#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/UseCases.hpp>

USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace fakeit;

class LocalAlbumArtServiceMock {
public:
    static Mock<ILocalAlbumArtService> getMockWithUrlNotOk() {
        Mock<ILocalAlbumArtService> mock;
        When(Method(mock, getUrl)).AlwaysReturn("/tmp/songId");
        When(Method(mock, isSongArtReady)).AlwaysReturn(false);
        return mock;
    }
    static Mock<ILocalAlbumArtService> getMockWithUrlOk() {
        Mock<ILocalAlbumArtService> mock;
        When(Method(mock, getUrl)).AlwaysReturn("/tmp/songId");
        When(Method(mock, isSongArtReady)).AlwaysReturn(true);
        return mock;
    }
};
