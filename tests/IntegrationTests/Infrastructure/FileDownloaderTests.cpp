#include <MellowPlayer/Infrastructure/FileDownloader.hpp>
#include <QtCore/QTemporaryDir>
#include <QtTest/qtestsystem.h>
#include <catch.hpp>

using namespace MellowPlayer::Infrastructure;

SCENARIO("FileDownloader can download a release source archive")
{
    FileDownloader downloader;
    QTemporaryDir dir;
    QString destination = dir.path() + "/MellowPlayer.zip";
    REQUIRE(!QFileInfo::exists(destination));

    WHEN("downloading MellowPlayer.zip from github")
    {
        downloader.download("https://github.com/ColinDuquesnoy/MellowPlayer/archive/2.95.0.zip", destination);

        THEN("progress is updated regularly until download has finished")
        {
            double latestProgress = -1;
            while (downloader.isDownloading()) {
                QTest::qWait(1);
                bool validProgressUpdate = downloader.progress() >= latestProgress || downloader.progress() == 0;
                REQUIRE(validProgressUpdate);
                latestProgress = downloader.progress();
            }

            AND_THEN("destination file exists")
            {
                REQUIRE(QFileInfo::exists(destination));
                REQUIRE(QFileInfo(destination).size() == 20396818);
            }
        }
    }
}
