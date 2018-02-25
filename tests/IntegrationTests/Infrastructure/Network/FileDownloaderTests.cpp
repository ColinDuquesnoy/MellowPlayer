#include <MellowPlayer/Infrastructure/Network/FileDownloader.hpp>
#include <QtCore/QTemporaryDir>
#include <QtTest/qtestsystem.h>
#include <catch/catch.hpp>

using namespace MellowPlayer::Infrastructure;

SCENARIO("FileDownloader can download a release source archive")
{
    FileDownloader downloader;
    QTemporaryDir dir;
    QString destination = dir.path() + "/MellowPlayer.zip";
    dir.setAutoRemove(false);
    REQUIRE(!QFileInfo::exists(destination));

    WHEN("downloading MellowPlayer.zip from github")
    {
        downloader.download("http://github.com/ColinDuquesnoy/MellowPlayer/archive/3.0.0.zip", destination);

        THEN("progress is updated regularly until download has finished")
        {
            double latestProgress = -1;
            while (downloader.isDownloading()) {
                QTest::qWait(1);
                bool validProgressUpdate = downloader.progress() >= latestProgress || downloader.progress() == 0;
                CAPTURE(latestProgress);
                REQUIRE(validProgressUpdate);
                latestProgress = downloader.progress();
            }

            AND_THEN("destination file exists")
            {
                CAPTURE(destination.toStdString());
                REQUIRE(QFileInfo::exists(destination));
                REQUIRE(QFileInfo(destination).size() != 20396818);
            }
        }
    }
}
