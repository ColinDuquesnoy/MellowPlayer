#include "WebPlayerPlugin.hpp"
#include "WebPlayerScript.hpp"
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>

using namespace std;
using namespace MellowPlayer;
using namespace MellowPlayer::Infrastructure;

WebPlayerPlugin::WebPlayerPlugin(const QString& path,
                                 IFactory<Domain::WebPlayerScript, QString>& webPlayerScriptFactory,
                                 IFactory<Domain::PluginMetadata, QString>& pluginMetadataFactory,
                                 IFactory<IIniFile, QString>& iniFileFactory,
                                 Domain::ISettingsStore& settingsStore):
    webPlayerScriptFactory_(webPlayerScriptFactory),
    pluginMetadataFactory_(pluginMetadataFactory),
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
    auto scriptPath = filePath("integration.js");
    script_ = webPlayerScriptFactory_.create(move(scriptPath));
    script_->load();
}

void WebPlayerPlugin::loadMetadata()
{
    auto metadataPath = filePath("metadata.ini");
    metadata_ = pluginMetadataFactory_.create(move(metadataPath));
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
