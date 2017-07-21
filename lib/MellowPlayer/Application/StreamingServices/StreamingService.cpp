#include "StreamingService.hpp"
#include "StreamingServiceScript.hpp"
#include <MellowPlayer/Application/Player/IPlayer.hpp>
#include <QtGui/QIcon>
#include <memory>

using namespace MellowPlayer::Application;
using namespace std;

StreamingService::StreamingService(const StreamingServiceMetadata &metadata, const Theme &theme)
        : metadata(metadata),
          theme(theme),
          script(make_unique<StreamingServiceScript>(metadata.script, metadata.scriptPath))
{
}

StreamingService::~StreamingService() = default;

const QString &StreamingService::getAuthor() const
{
    return metadata.author;
}

const QString &StreamingService::getAuthorWebsite() const
{
    return metadata.authorWebsite;
}

QString StreamingService::getLogo() const
{
    if (metadata.logoPath.isEmpty())
        return "";
#ifdef Q_OS_WIN
    return "file:" + metadata.logoPath;
#else
    return "file://" + metadata.logoPath;
#endif
}

const QString &StreamingService::getName() const
{
    return metadata.name;
}

QString StreamingService::getUrl() const
{
    return metadata.url;
}

const QString &StreamingService::getVersion() const
{
    return metadata.version;
}

bool StreamingService::isValid() const
{
    return metadata.isValid() && script->isValid();
}

StreamingServiceScript *StreamingService::getScript() const
{
    return script.get();
}

const Theme &StreamingService::getTheme() const
{
    return theme;
}

bool StreamingService::operator==(const StreamingService &rhs) const
{
    return getName() == rhs.getName();
}

bool StreamingService::operator!=(const StreamingService &rhs) const
{
    return !operator==(rhs);
}

void StreamingService::updateTheme(Theme &newTheme)
{
    theme = newTheme;
    emit themeChanged();
}

void StreamingService::updateScript(const QString &scriptCode)
{
    script->setCode(scriptCode);
    emit scriptChanged();
}

QString StreamingService::getPluginDirectory() const
{
    return metadata.pluginDirectory;
}
