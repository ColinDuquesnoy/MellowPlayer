#include <MellowPlayer/Presentation/ViewModels/CookiesViewModel.hpp>
#include <UnitTests/Presentation/Qml/FakeContextProperties.hpp>
#include <catch/catch.hpp>
#include <QtWebEngineWidgets/QWebEngineProfile>
#include <QtCore/QDir>

using namespace MellowPlayer::Presentation;
using namespace MellowPlayer::Presentation::Tests;

SCENARIO("CookiesViewModelTests")
{
    FakeContextProperties contextProperties;
    CookiesViewModel cookies(contextProperties);
    
    GIVEN("a cookies directory with some cookies files in it")
    {
        QWebEngineProfile profile("Default");
        QString cookiesPath = profile.persistentStoragePath();

        QDir cacheDir(cookiesPath);
        cacheDir.mkpath(cookiesPath);
        cacheDir.mkdir(cookiesPath + QDir::separator() + "SubDir1");
        cacheDir.mkdir(cookiesPath + QDir::separator() + "SubDir2");
        QStringList paths = {
                cookiesPath + QDir::separator() + "file",
                cookiesPath + QDir::separator() + "SubDir1" + "file",
                cookiesPath + QDir::separator() + "SubDir2" + "file",
        };
        for(auto& path: paths) {
            QFile file(path);
            file.open(QFile::WriteOnly);
            file.write("foot");
        }

        REQUIRE(!cacheDir.isEmpty());
        
        WHEN("I clear the cookies")
        {
            cookies.clear();

            THEN("operation was successfully accomplished")
            {
                REQUIRE(cacheDir.isEmpty());
            }
        }
    }
}
