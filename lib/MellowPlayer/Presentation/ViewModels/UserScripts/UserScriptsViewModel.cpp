#include "UserScriptsViewModel.hpp"
#include <MellowPlayer/Application/UserScripts/IUserScript.hpp>
using namespace MellowPlayer::Application;
using namespace MellowPlayer::Presentation;


UserScriptsViewModel::UserScriptsViewModel(const QString& serviceName,
                                           IUserScriptFactory& userScriptFactory,
                                           ISettingsProvider& settingsProvider,
                                           QObject* parent):
    QObject(parent),
    userScripts_(serviceName, userScriptFactory, settingsProvider)
{
    for(auto* userScriptModel: userScripts_) {
        create(*userScriptModel);
    }
}

QAbstractListModel* UserScriptsViewModel::model()
{
    return &model_;
}

bool UserScriptsViewModel::isValidName(const QString& name) const
{
    QStringList names;

    for(auto* userScriptModel: userScripts_)
        names.append(userScriptModel->name());

    return !names.contains(name);
}

void UserScriptsViewModel::add(const QString& name, const QString& sourcePath)
{
    IUserScript& userScriptModel = userScripts_.add(name, sourcePath);

    create(userScriptModel);
}

void UserScriptsViewModel::remove(const QString& name)
{
    for (int i = 0; i < model_.count(); ++i) {
        if (model_.at(i)->name() == name) {
            model_.remove(i);
        }
    }
    userScripts_.remove(name);
}


void UserScriptsViewModel::create(IUserScript& userScriptModel)
{
    auto* userScriptViewModel = new UserScriptViewModel(userScriptModel, this);
    model_.append(userScriptViewModel);
}
