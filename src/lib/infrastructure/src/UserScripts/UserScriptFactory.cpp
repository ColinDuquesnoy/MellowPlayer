#include <MellowPlayer/Infrastructure/UserScripts/UserScriptFactory.hpp>
#include <MellowPlayer/Infrastructure/UserScripts/UserScript.hpp>

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

IUserScript* MellowPlayer::Infrastructure::UserScriptFactory::create() const
{
    return new UserScript;
}
