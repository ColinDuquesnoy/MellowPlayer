#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceCreator.hpp>
#include <MellowPlayer/Infrastructure/StreamingServices/StreamingServiceLoader.hpp>
#include <MellowPlayer/Infrastructure/Helpers/FileHelper.hpp>
#include <QDebug>
#include <QtCore/QDir>

using namespace std;
using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

const QString StreamingServiceCreator::RESOURCE_PATH = ":/MellowPlayer/Infrastructure/PluginTemplate/%1";
const QString StreamingServiceCreator::SCRIPT_FILE_NAME = "integration.js";
const QString StreamingServiceCreator::LOGO_FILE_NAME = "logo.svg";
const QString StreamingServiceCreator::METADATA_FILE_NAME = "metadata.ini";
const QString StreamingServiceCreator::THEME_FILE_NAME = "theme.json";

QString StreamingServiceCreator::create(const QString& serviceName, const QString& serviceUrl, const QString& authorName,
                                        const QString& authorWebsite, const QString& supportedPlatforms) const
{
    auto dir = pluginDir(serviceName);
    QDir().mkpath(dir);

    createLogo(dir);
    createScript(dir);
    createTheme(dir);
    createMetadata(serviceName, serviceUrl, authorName, authorWebsite, supportedPlatforms, dir);

    return dir;
}

void StreamingServiceCreator::createScript(const QString& pluginDir) const
{
    createPluginFile(pluginDir, SCRIPT_FILE_NAME);
}

void StreamingServiceCreator::createLogo(const QString& pluginDir) const
{
    createPluginFile(pluginDir, LOGO_FILE_NAME);
}

void StreamingServiceCreator::createTheme(const QString& pluginDir) const
{
    createPluginFile(pluginDir, THEME_FILE_NAME);
}

void StreamingServiceCreator::createMetadata(const QString& serviceName, const QString& serviceUrl, const QString& authorName,
                                             const QString& authorWebsite, const QString& supportedPlatforms, const QString& pluginDir) const
{
    createPluginFile(pluginDir, METADATA_FILE_NAME, [&](QString string) {
        return string.arg(authorName, authorWebsite, serviceName, supportedPlatforms, serviceUrl); });
}

QString StreamingServiceCreator::pluginDir(const QString& serviceName) const
{
    return QDir::cleanPath(StreamingServiceLoader::userDirectory() + QDir::separator() + serviceName);
}

QString StreamingServiceCreator::readTemplateFile(const QString& fileName) const
{
    QFile file(QString(RESOURCE_PATH).arg(fileName));

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";

    QTextStream in(&file);
    return in.readAll();
}

void StreamingServiceCreator::write(const QString& path, const QString& content) const
{
    QFile file(path);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << content;
    }
}

QString StreamingServiceCreator::filePath(const QString& pluginDir, const QString& fileName) const
{
    return QDir::cleanPath(pluginDir + QDir::separator() + fileName);
}

void StreamingServiceCreator::createPluginFile(const QString& pluginDir, const QString& fileName, const function<QString(QString)>& transformer) const
{
    const QString path = filePath(pluginDir, fileName);
    const QString content = transformer(readTemplateFile(fileName));
    write(path, content);
}
