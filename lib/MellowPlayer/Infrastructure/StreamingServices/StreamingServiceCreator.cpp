#include "StreamingServiceCreator.hpp"
#include "StreamingServiceLoader.hpp"
#include <MellowPlayer/Infrastructure/Helpers/FileHelper.hpp>
#include <QtCore/QDir>
#include <QtCore/QTextStream>
#include <QDebug>

using namespace std;
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

const QString StreamingServiceCreator::RESOURCE_PATH = ":/MellowPlayer/Application/PluginTemplate/%1";
const QString StreamingServiceCreator::SCRIPT_FILE_NAME = "integration.js";
const QString StreamingServiceCreator::LOGO_FILE_NAME = "logo.svg";
const QString StreamingServiceCreator::METADATA_FILE_NAME = "metadata.ini";
const QString StreamingServiceCreator::THEME_FILE_NAME = "theme.json";

QString StreamingServiceCreator::create(const QString& serviceName, const QString& serviceUrl,
                                        const QString& authorName, const QString& authorWebsite) const {
    auto pluginDir = getPluginDir(serviceName);
    QDir().mkpath(pluginDir);

    createLogo(pluginDir);
    createScript(pluginDir);
    createTheme(pluginDir);
    createMetadata(serviceName, serviceUrl, authorName, authorWebsite, pluginDir);

    return pluginDir;
}

void StreamingServiceCreator::createScript(const QString& pluginDir) const {
    createPluginFile(pluginDir, SCRIPT_FILE_NAME);
}

void StreamingServiceCreator::createLogo(const QString& pluginDir) const {
    createPluginFile(pluginDir, LOGO_FILE_NAME);
}

void StreamingServiceCreator::createTheme(const QString& pluginDir) const {
    createPluginFile(pluginDir, THEME_FILE_NAME);
}

void StreamingServiceCreator::createMetadata(const QString& serviceName, const QString& serviceUrl,
                                                   const QString& authorName, const QString& authorWebsite,
                                                   const QString& pluginDir) const {
    createPluginFile(pluginDir, METADATA_FILE_NAME, [&](QString string) {
        return string.arg(authorName, authorWebsite, serviceName, serviceUrl);
    });
}

QString StreamingServiceCreator::getPluginDir(const QString& serviceName) const {
    return QDir::cleanPath(StreamingServiceLoader::getUserDirectory() + QDir::separator() + serviceName);
}

QString StreamingServiceCreator::readTemplateFile(const QString& fileName) const {
    QFile file(QString(RESOURCE_PATH).arg(fileName));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";

    QTextStream in(&file);
    return in.readAll();
}

void StreamingServiceCreator::write(const QString& path, const QString& content) const {
    QFile file(path);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << content;
    }
}

QString StreamingServiceCreator::getFilePath(const QString& pluginDir, const QString& fileName) const {
    return QDir::cleanPath(pluginDir + QDir::separator() + fileName);
}

void StreamingServiceCreator::createPluginFile(const QString& pluginDir, const QString& fileName,
                                                     const function<QString(QString)> transformer) const {
    const QString filePath = getFilePath(pluginDir, fileName);
    const QString content = transformer(readTemplateFile(fileName));
    write(filePath, content);
}
