#pragma once

#include <QList>

namespace MellowPlayer::Application
{
    class ISettingsProvider;
    class IUserScript;
    
    class UserScripts
    {
    public:
        UserScripts(const QString& serviceName, ISettingsProvider& settingsProvider);
        ~UserScripts();
        
        int count() const;
        void add(IUserScript* userScript);
        void remove(const QString& scriptName);
        
        typedef typename QList<IUserScript*>::const_iterator const_iterator;
        const_iterator begin(void) const;
        const_iterator end(void) const;

    private:
        QString serviceName_;
        ISettingsProvider& settingsProvider_;
        QList<IUserScript*> _scripts;        
    };
}
