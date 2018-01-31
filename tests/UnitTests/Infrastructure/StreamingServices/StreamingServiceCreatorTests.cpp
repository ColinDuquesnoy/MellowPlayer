#include "Utils/Helpers.hpp"
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceCreator.hpp>
#include <QtCore/QDir>
#include <catch/catch.hpp>
#include <iostream>

using namespace MellowPlayer::Infrastructure;

TEST_CASE("StreamingServiceCreatorTests")
{
    StreamingServiceCreator creator;
    auto pluginDir = creator.create("TestService", "https://test-service.com", "MellowPlayer.Tests", "All", "https://travis-ci.org/MellowPlayer");
    REQUIRE(QDir(pluginDir).exists());
    QList<QFileInfo> files;
    files.append(QFileInfo(pluginDir + "/" + "integration.js"));
    files.append(QFileInfo(pluginDir + "/" + "logo.svg"));
    files.append(QFileInfo(pluginDir + "/" + "theme.json"));
    files.append(QFileInfo(pluginDir + "/" + "metadata.ini"));

    for (auto fileInfo : files) {
        REQUIRE(fileInfo.exists());
        REQUIRE(!readFile(fileInfo.absoluteFilePath()).isEmpty());
    }
    QDir().rmpath(pluginDir);
}
