#pragma once
#include <MellowPlayer/Application/AlbumArt/ILocalAlbumArt.hpp>
#include <fakeit.hpp>
#include <memory>

using namespace MellowPlayer::Application;
using namespace fakeit;

class LocalAlbumArtMock
{
public:
    static Mock<ILocalAlbumArt> getMockWithUrlNotOk()
    {
        Mock<ILocalAlbumArt> mock;
        When(Method(mock, getUrl)).AlwaysReturn("/tmp/songId");
        When(Method(mock, isSongArtReady)).AlwaysReturn(false);
        return mock;
    }
    static Mock<ILocalAlbumArt> getMockWithUrlOk()
    {
        Mock<ILocalAlbumArt> mock;
        When(Method(mock, getUrl)).AlwaysReturn("/tmp/songId");
        When(Method(mock, isSongArtReady)).AlwaysReturn(true);
        return mock;
    }
};
