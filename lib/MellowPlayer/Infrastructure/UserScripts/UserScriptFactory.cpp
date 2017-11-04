#include "UserScriptFactory.hpp"
#include "UserScript.hpp"

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Infrastructure;

IUserScript* MellowPlayer::Infrastructure::UserScriptFactory::create() const
{
    return new UserScript;
}
