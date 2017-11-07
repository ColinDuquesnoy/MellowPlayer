#include "WebPlayerPlugin.hpp"
#include "WebPlayerScript.hpp"
#include "PluginMetadata.hpp"
#include <MellowPlayer/Domain/Settings/ISettingsStore.hpp>
#include <iostream>

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
    cout << "Creating integration script" << endl;
    script_ = make_shared<WebPlayerScript>(fileFactory_.create(filePath("integration.js")));
    cout << "Loading integration script" << endl;
    script_->load();
}

void WebPlayerPlugin::loadMetadata()
{
    cout << "Creating metadata" << endl;
    metadata_ = make_shared<PluginMetadata>(iniFileFactory_.create(filePath("metadata.ini")));
    cout << "Loading metadata" << endl;
    metadata_->load();
}

void WebPlayerPlugin::loadUrl()
{
    cout << "Create metadata file to read url" << endl;
    auto iniFile = iniFileFactory_.create(filePath("metadata.ini"));
    cout << "Reading url" << endl;
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
