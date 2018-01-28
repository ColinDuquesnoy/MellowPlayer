#include <MellowPlayer/Presentation/ViewModels/UserScripts/UserScriptViewModel.hpp>
#include <MellowPlayer/Domain/UserScripts/IUserScript.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Presentation;

UserScriptViewModel::UserScriptViewModel(IUserScript& model, QObject* parent):
    QObject(parent), model_(model)
{

}

QString UserScriptViewModel::name() const
{
    return model_.name();
}

void UserScriptViewModel::setName(const QString& name)
{
    Q_UNUSED(name);
    if (name != model_.name()) {
        model_.setName(name);
        emit nameChanged();
    }
}

QString UserScriptViewModel::code() const
{
    return model_.code();
}

QString UserScriptViewModel::path() const
{
    return model_.path();
}

IUserScript& UserScriptViewModel::model()
{
    return model_;
}
