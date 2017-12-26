#include <MellowPlayer/Presentation/ViewModels/CacheViewModel.hpp>
#include <UnitTests/Presentation/Qml/FakeContextProperties.hpp>
#include <catch/catch.hpp>
#include <QtCore/QStandardPaths>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QtTest/qtestsystem.h>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;

SCENARIO("CacheViewModelTests")
{
    FakeContextProperties contextProperties;
    CacheViewModel cache(contextProperties);

    GIVEN("A cache directory with some files in the root directory and two sub-directories")
    {
        auto cachePath = QStandardPaths::standardLocations(QStandardPaths::CacheLocation)[0];
        QDir cacheDir(cachePath);
        cacheDir.mkpath(cachePath);
        cacheDir.mkdir(cachePath + QDir::separator() + "SubDir1");
        cacheDir.mkdir(cachePath + QDir::separator() + "SubDir2");
        QStringList paths = {
                cachePath + QDir::separator() + "file",
                cachePath + QDir::separator() + "SubDir1" + "file",
                cachePath + QDir::separator() + "SubDir2" + "file",
        };
        for(auto& path: paths) {
            QFile file(path);
            file.open(QFile::WriteOnly);
            file.write("foot");
        }

        REQUIRE(!cacheDir.isEmpty());

        WHEN("I clear the cache")
        {
            cache.clear();

            QTest::qWait(1000);

            THEN("cache is empty")
            {
                REQUIRE(!QFileInfo::exists(cachePath + QDir::separator() + "SubDir1"));
                REQUIRE(!QFileInfo::exists(cachePath + QDir::separator() + "SubDir2"));
                REQUIRE(!QFileInfo::exists(paths[0]));
                REQUIRE(!QFileInfo::exists(paths[1]));
                REQUIRE(!QFileInfo::exists(paths[2]));
            }
        }
    }
}
