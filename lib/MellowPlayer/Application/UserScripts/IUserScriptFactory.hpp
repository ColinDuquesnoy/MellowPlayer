#pragma once

namespace MellowPlayer::Application
{
    class IUserScript;

    class IUserScriptFactory
    {
    public:
        virtual ~IUserScriptFactory() = default;
        virtual IUserScript* create() const = 0;
    };
}