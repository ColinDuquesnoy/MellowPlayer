#include <MellowPlayer/Infrastructure/AlbumArt/AlbumArtDownloader.hpp>
#include <QtTest/QSignalSpy>
#include <catch.hpp>
#include <iostream>
using namespace MellowPlayer::Infrastructure;

TEST_CASE("AlbumArtDownloaderTests")
{
    AlbumArtDownloader albumArtDownloader;
    QSignalSpy downloadFinishedSpy(&albumArtDownloader, SIGNAL(downloadFinished(const QString &)));

    QFile::remove(albumArtDownloader.getLocalArtUrl("mellowplayer.svg").absoluteFilePath());

    SECTION("download will take some time and a file will be created")
    {
        REQUIRE(albumArtDownloader.download("https://gitlab.com/uploads/project/avatar/2312266/mellowplayer.svg",
                                            "mellowplayer.svg"));
        if (downloadFinishedSpy.wait(2000)) {
            REQUIRE(downloadFinishedSpy.count() == 1);
            auto path = downloadFinishedSpy[0][0].toString();
            REQUIRE(!path.isEmpty());
            REQUIRE(QFile(path).exists());

            SECTION("second download is immediate")
            {
                albumArtDownloader.download("https://gitlab.com/uploads/project/avatar/"
                                            "2312266/mellowplayer.svg",
                                            "mellowplayer.svg");
                REQUIRE(downloadFinishedSpy.count() == 2);
            }
        }
    }

    SECTION("no download if empty url")
    {
        REQUIRE(!albumArtDownloader.download("", "mellowplayer.svg"));
    }

    SECTION("no download if empty song id")
    {
        REQUIRE(!albumArtDownloader.download("https://gitlab.com/uploads/project/avatar/2312266/mellowplayer.svg", ""));
    }
}
