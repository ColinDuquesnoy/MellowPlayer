#include <MellowPlayer/Presentation/ViewModels/UserScripts/UserScriptsViewModel.hpp>
#include <MellowPlayer/Domain/UserScripts/IUserScript.hpp>
#include <QFileInfo>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

UserScriptsViewModel::UserScriptsViewModel(const QString& serviceName,
                                           IUserScriptFactory& userScriptFactory,
                                           ISettingsStore& settingsStore,
                                           QObject* parent):
    QObject(parent),
    userScripts_(serviceName, userScriptFactory, settingsStore)
{
    for(auto* userScriptModel: userScripts_) {
        create(userScriptModel);
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

bool UserScriptsViewModel::add(const QString& name, const QString& sourcePath)
{
    bool hadUserScripts = hasScripts();
    IUserScript* userScriptModel = userScripts_.add(name, sourcePath);
    if (userScriptModel != nullptr) {
        create(userScriptModel);
        if (hadUserScripts != hasScripts())
            emit hasScriptsChanged();

        return true;
    }

    return false;
}

void UserScriptsViewModel::remove(const QString& name)
{
    bool hadUserScripts = hasScripts();
    for (int i = 0; i < model_.count(); ++i) {
        if (model_.at(i)->name() == name) {
            model_.remove(i);
        }
    }
    userScripts_.remove(name);

    if (hadUserScripts != hasScripts())
        emit hasScriptsChanged();
}


void UserScriptsViewModel::create(IUserScript* userScriptModel)
{
    auto* userScriptViewModel = new UserScriptViewModel(*userScriptModel, this);
    model_.append(userScriptViewModel);
}

bool UserScriptsViewModel::hasScripts() const
{
    return userScripts_.count() != 0;
}

QString UserScriptsViewModel::generateUniqueName(const QString& path) const
{
    QFileInfo fileInfo(path);
    QString baseName = fileInfo.baseName();
    QString name = baseName;

    int i = 1;
    while(!isValidName(name)) {
        ++i;
        name = baseName + QString::number(i);
    }

    return name;
}
