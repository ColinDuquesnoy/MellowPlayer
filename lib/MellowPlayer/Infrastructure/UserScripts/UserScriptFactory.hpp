#pragma once

#include <MellowPlayer/Application/UserScripts/IUserScriptFactory.hpp>

namespace MellowPlayer::Infrastructure
{
    class UserScriptFactory: public Application::IUserScriptFactory
    {
    public:
        Application::IUserScript* create() const override;

    };
}
