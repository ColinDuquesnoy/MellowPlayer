#include <catch.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceCreator.hpp>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QTextStream>
#include <iostream>
#include "Utils/Helpers.hpp"

using namespace MellowPlayer::Infrastructure;

TEST_CASE("StreamingServiceCreatorTests") {
    StreamingServiceCreator creator;
    auto pluginDir = creator.create("TestService", "https://test-service.com", "MellowPlayer.Tests", "https://travis-ci.org/MellowPlayer");
    REQUIRE(QDir(pluginDir).exists());
    QList<QFileInfo> files;
    files.append(QFileInfo(pluginDir + "/" + "integration.js"));
    files.append(QFileInfo(pluginDir + "/" + "logo.svg"));
    files.append(QFileInfo(pluginDir + "/" + "style.json"));
    files.append(QFileInfo(pluginDir + "/" + "metadata.ini"));

    for(auto fileInfo: files) {
        std::cerr << fileInfo.absoluteFilePath().toStdString() << std::endl;
        REQUIRE(fileInfo.exists());
        REQUIRE(!readFile(fileInfo.absoluteFilePath()).isEmpty());
    }
    QDir().rmpath(pluginDir);
}
