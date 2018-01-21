#pragma once

#include <QObject>
#include <MellowPlayer/Domain/UserScripts/UserScripts.hpp>
#include <MellowPlayer/Presentation/Models/UserScriptListModel.hpp>

namespace MellowPlayer::Presentation
{
    class UserScriptsViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(bool hasScripts READ hasScripts NOTIFY hasScriptsChanged)
        Q_PROPERTY(QAbstractListModel* model READ model CONSTANT)
    public:
        UserScriptsViewModel(const QString& serviceName,
                             Domain::IUserScriptFactory& userScriptFactory,
                             Domain::ISettingsStore& settingsStore,
                             QObject* parent= nullptr);

        QAbstractListModel* model();
        bool hasScripts() const;

        Q_INVOKABLE QString generateUniqueName(const QString& path) const;
        Q_INVOKABLE bool isValidName(const QString& name) const;
        Q_INVOKABLE bool add(const QString& name, const QString& sourcePath);
        Q_INVOKABLE void remove(const QString& name);

    signals:
        void hasScriptsChanged();

    private:
        void create(Domain::IUserScript* userScriptModel);

        Domain::UserScripts userScripts_;
        UserScriptListModel model_;
    };
}
