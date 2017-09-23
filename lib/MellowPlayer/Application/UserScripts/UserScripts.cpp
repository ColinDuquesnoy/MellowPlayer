#include "IUserScript.hpp"
#include "UserScripts.hpp"
#include <MellowPlayer/Application/Settings/ISettingsProvider.hpp>

using namespace MellowPlayer::Application;

UserScripts::UserScripts(const QString& serviceName, ISettingsProvider& settingsProvider):
    serviceName_(serviceName),
    settingsProvider_(settingsProvider)
{
    auto scriptPaths = settingsProvider.value(serviceName + "/userScriptPaths", QStringList()).toStringList();
    auto scriptNames = settingsProvider.value(serviceName + "/userScriptNames", QStringList()).toStringList();

    for (int i = 0; scriptPaths.count(); ++i) {
        auto path = scriptPaths[i];
        auto name = scriptNames[i];
    }
}

UserScripts::~UserScripts()
{
    qDeleteAll(_scripts);
}

int UserScripts::count() const
{
    return 0;
}

void UserScripts::add(IUserScript* userScript)
{
    Q_UNUSED(userScript);
}

void UserScripts::remove(const QString& scriptName)
{
    Q_UNUSED(scriptName);
}

UserScripts::const_iterator UserScripts::begin(void) const
{
    return _scripts.begin();
}

UserScripts::const_iterator UserScripts::end(void) const
{
    return _scripts.end();
}
