#pragma once

#include <QList>

namespace MellowPlayer::Domain
{
    class ISettingsStore;
    class IUserScript;
    class IUserScriptFactory;
    class ILogger;

    class UserScripts
    {
    public:
        UserScripts(const QString& serviceName,
                    IUserScriptFactory& userScriptFactory,
                    ISettingsStore& settingsStore);
        ~UserScripts();

        int count() const;
        IUserScript* add(const QString& userScriptName, const QString& sourceScriptPath);
        void remove(const QString& scriptName);

        typedef typename QList<IUserScript*>::const_iterator const_iterator;
        const_iterator begin(void) const;
        const_iterator end(void) const;

    private:
        QString pathsKey() const;
        QString namesKey() const;

        QString serviceName_;
        IUserScriptFactory& userScriptFactory_;
        ISettingsStore& settingsStore_;
        QList<IUserScript*> _scripts;
        ILogger& _logger;

        void save(const QString& userScriptName, const IUserScript* userScript) const;
    };
}
