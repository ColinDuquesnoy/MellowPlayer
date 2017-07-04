#include <catch.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceCreator.hpp>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QTextStream>

USING_MELLOWPLAYER_NAMESPACE(Infrastructure)

QString readFile(const QString& path) {
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";

    QTextStream in(&file);
    return in.readAll();
}

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
        CAPTURE("file: " + fileInfo.absoluteFilePath().toStdString());
        REQUIRE(fileInfo.exists());
        REQUIRE(!readFile(fileInfo.absoluteFilePath()).isEmpty());
    }
    QDir().rmpath(pluginDir);
}
