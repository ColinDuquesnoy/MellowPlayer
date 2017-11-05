#include "WebPlayerPlugin.hpp"
#include "WebPlayerScript.hpp"
#include "PluginMetadata.hpp"
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>

using namespace std;
using namespace MellowPlayer;
using namespace MellowPlayer::Infrastructure;

WebPlayerPlugin::WebPlayerPlugin(const QString& path,
                                 IFactory<IFile, QString>& fileFactory,
                                 IFactory<IIniFile, QString>& iniFileFactory,
                                 Domain::ISettingsStore& settingsStore):
    fileFactory_(fileFactory),
    iniFileFactory_(iniFileFactory),
    settingsStore_(settingsStore)
{
    path_ = path;
}

void WebPlayerPlugin::load()
{
    loadIntegrationScript();
    loadMetadata();
    loadUrl();

//    setEnabled(settingsStore_.value(isEnabledSettingsKey(), true).toBool());
}

void WebPlayerPlugin::loadIntegrationScript()
{
    script_ = make_shared<WebPlayerScript>(fileFactory_.create(filePath("integration.js")));
    script_->load();
}

void WebPlayerPlugin::loadMetadata()
{
    metadata_ = make_shared<PluginMetadata>(iniFileFactory_.create(filePath("metadata.ini")));
    metadata_->load();
}

void WebPlayerPlugin::loadUrl()
{
    auto iniFile = iniFileFactory_.create(filePath("metadata.ini"));
    url_ = iniFile->value("url").toString();
}

QString Infrastructure::WebPlayerPlugin::customUrlSettingsKey() const
{
    return metadata_->name() + "/url";
}

QString Infrastructure::WebPlayerPlugin::isEnabledSettingsKey() const
{
    return metadata_->name() + "/isEnabled";
}

QString WebPlayerPlugin::filePath(const QString& fileName) const
{
    return path_ + QDir::separator() + fileName;
}
