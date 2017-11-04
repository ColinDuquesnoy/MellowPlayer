#pragma once

#include <MellowPlayer/Domain/UserScripts/IUserScriptFactory.hpp>

namespace MellowPlayer::Infrastructure
{
    class UserScriptFactory: public Domain::IUserScriptFactory
    {
    public:
        Domain::IUserScript* create() const override;

    };
}
