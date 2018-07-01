#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServiceScript.hpp>
#include <MellowPlayer/Domain/Player/IPlayer.hpp>
#include <QtGui/QIcon>

using namespace MellowPlayer::Domain;
using namespace std;

StreamingService::StreamingService(const StreamingServiceMetadata& metadata, const Theme& theme, const std::shared_ptr<SettingsCategory> &settings)
        : metadata_(metadata),
          theme_(theme),
          _settings(settings),
          script_(make_unique<StreamingServiceScript>(metadata.script, metadata.scriptPath))
{
}

StreamingService::~StreamingService() = default;

const QString& StreamingService::author() const
{
    return metadata_.author;
}

const QString& StreamingService::authorWebsite() const
{
    return metadata_.authorWebsite;
}

QString StreamingService::logo() const
{
    if (metadata_.logoPath.isEmpty())
        return "";
#ifdef Q_OS_WIN
    return "file:" + metadata_.logoPath;
#else
    return "file://" + metadata_.logoPath;
#endif
}

const QString& StreamingService::name() const
{
    return metadata_.name;
}

QString StreamingService::url() const
{
    return metadata_.url;
}

const QString& StreamingService::version() const
{
    return metadata_.version;
}

bool StreamingService::isValid() const
{
    return metadata_.isValid() && script_->isValid();
}

StreamingServiceScript* StreamingService::script() const
{
    return script_.get();
}

const Theme& StreamingService::theme() const
{
    return theme_;
}

bool StreamingService::operator==(const StreamingService& rhs) const
{
    return name() == rhs.name();
}

bool StreamingService::operator!=(const StreamingService& rhs) const
{
    return !operator==(rhs);
}

SettingsCategory* StreamingService::settings() const
{
    return _settings.get();
}

void StreamingService::updateTheme(Theme& newTheme)
{
    theme_ = newTheme;
    emit themeChanged();
}

void StreamingService::updateScript(const QString& scriptCode)
{
    script_->setCode(scriptCode);
    emit scriptChanged();
}

QString StreamingService::pluginDirectory() const
{
    return metadata_.pluginDirectory;
}
