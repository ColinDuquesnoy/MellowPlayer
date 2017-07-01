#include <memory>
#include <QtGui/QIcon>
#include <MellowPlayer/Application/Player/IPlayer.hpp>
#include "StreamingService.hpp"
#include "StreamingServiceScript.hpp"

USING_MELLOWPLAYER_NAMESPACE(Application)
using namespace std;

StreamingService::StreamingService(const StreamingServiceMetadata& metadata,  const StreamingServiceStyle& style):
    metadata(metadata), style(style), script(make_unique<StreamingServiceScript>(metadata.script, metadata.scriptPath)) {
}

StreamingService::~StreamingService() = default;

const QString& StreamingService::getAuthor() const {
    return metadata.author;
}

const QString& StreamingService::getAuthorWebsite() const {
    return metadata.authorWebsite;
}

QString StreamingService::getColor() const {
    if (QColor(metadata.color).isValid())
        return metadata.color;
    return "";
}

QString StreamingService::getLogo() const {
    if (metadata.logoPath.isEmpty())
        return "";
#ifdef Q_OS_WIN
    return "file:" + metadata.logoPath;
#else
    return "file://" + metadata.logoPath;
#endif
}

const QString& StreamingService::getName() const {
    return metadata.name;
}

QString StreamingService::getUrl() const {
    return metadata.url;
}

const QString& StreamingService::getVersion() const {
    return metadata.version;
}

bool StreamingService::isValid() const {
    return metadata.isValid() && script->isValid();
}

StreamingServiceScript* StreamingService::getScript() const {
    return script.get();
}

const StreamingServiceStyle& StreamingService::getStyle() const {
    return style;
}

bool StreamingService::operator==(const StreamingService& rhs) const {
    return getName() == rhs.getName();
}

bool StreamingService::operator!=(const StreamingService& rhs) const {
    return !operator==(rhs);
}
