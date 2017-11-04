#pragma once

namespace MellowPlayer::Domain
{
    class IUserScript;

    class IUserScriptFactory
    {
    public:
        virtual ~IUserScriptFactory() = default;
        virtual IUserScript* create() const = 0;
    };
}