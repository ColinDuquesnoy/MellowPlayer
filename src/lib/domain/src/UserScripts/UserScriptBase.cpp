#include <MellowPlayer/Domain/UserScripts/UserScriptBase.hpp>

using namespace MellowPlayer::Domain;

QString UserScriptBase::path() const
{
    return path_;
}

QString UserScriptBase::code() const
{
    return code_;
}

QString UserScriptBase::name() const
{
    return name_;
}

void UserScriptBase::setName(const QString& name)
{
    name_ = name;
}
