#include "UserScriptFactory.hpp"
#include "UserScript.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

IUserScript* MellowPlayer::Infrastructure::UserScriptFactory::create() const
{
    return new UserScript;
}
