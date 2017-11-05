#include "WebPlayerPlugin.hpp"
#include "WebPlayerScript.hpp"
#include <MellowPlayer/Domain/Plugins/PluginMetadata.hpp>
#include <MellowPlayer/Domain/Plugins/WebPlayerScript.hpp>
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>

using namespace std;
using namespace MellowPlayer;
using namespace MellowPlayer::Infrastructure;

WebPlayerPlugin::WebPlayerPlugin(const QString& path,
                                 IFactory<Domain::WebPlayerScript, QString>& webPlayerScriptFactory,
                                 Domain::ISettingsStore& settingsStore):
    webPlayerScriptFactory_(webPlayerScriptFactory),
    settingsStore_(settingsStore)
{
    path_ = path;
}

void WebPlayerPlugin::load()
{
    loadIntegrationScript();
//    setEnabled(settingsStore_.value(isEnabledSettingsKey(), true).toBool());
}

void WebPlayerPlugin::loadIntegrationScript()
{
    auto scriptPath = path_ + QDir::separator() + "integration.js";
    script_ = webPlayerScriptFactory_.create(move(scriptPath));
    script_->load();
}

QString Infrastructure::WebPlayerPlugin::customUrlSettingsKey() const
{
    return metadata_->name() + "/url";
}

QString Infrastructure::WebPlayerPlugin::isEnabledSettingsKey() const
{
    return metadata_->name() + "/isEnabled";
}
