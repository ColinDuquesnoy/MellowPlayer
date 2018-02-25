#include <MellowPlayer/Infrastructure/AlbumArt/AlbumArtDownloader.hpp>
#include <QtTest/QSignalSpy>
#include <catch/catch.hpp>
#include <iostream>
#include <QtCore/QTemporaryDir>

using namespace MellowPlayer::Infrastructure;

TEST_CASE("AlbumArtDownloaderTests", "[!mayfail]")
{
    AlbumArtDownloader albumArtDownloader;
    QSignalSpy downloadFinishedSpy(&albumArtDownloader, SIGNAL(downloadFinished(const QString&)));

    QFile::remove(albumArtDownloader.localArtUrl("mellowplayer.svg").absoluteFilePath());

    SECTION("download will take some time and a file will be created")
    {
        QString url = "http://github.com/ColinDuquesnoy/MellowPlayer/blob/develop/docs/_static/banner.png";
        QString name = "banner.png";
        REQUIRE(albumArtDownloader.download(url, name));
        if (downloadFinishedSpy.wait(2000)) {
            REQUIRE(downloadFinishedSpy.count() == 1);
            auto path = downloadFinishedSpy[0][0].toString();
            CAPTURE(path.toStdString());
            REQUIRE(!path.isEmpty());
            REQUIRE(QFile(path).exists());

            SECTION("second download is immediate")
            {
                albumArtDownloader.download(url, name);
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

SCENARIO("AlbumArtDownloaderTests can download a base64 image")
{
    AlbumArtDownloader downloader;
    QTemporaryDir dir;
    QString destination = downloader.localArtUrl("songId").absoluteFilePath();
    QFile::remove(destination);
    QSignalSpy spy(&downloader, &AlbumArtDownloader::downloadFinished);

    WHEN("downloading valid base64 string")
    {
        QString validBase64Url = "data:image/jpeg;base64,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";
        downloader.download(validBase64Url, "songId");

        THEN("destination file exists")
        {
            REQUIRE(QFile::exists(destination));
        }

        AND_THEN("downloadFinished signal is emitted once")
        {
            REQUIRE(spy.count() == 1);
        }
    }

    WHEN("downloading invalid base64 string")
    {
        QString inValidBase64Url = "";
        downloader.download(inValidBase64Url, "songId");

        THEN("destination file does not exist")
        {
            REQUIRE(!QFile::exists(destination));
        }

        AND_THEN("downloadFinished signal is not emitted")
        {
            REQUIRE(spy.count() == 0);
        }
    }

}
