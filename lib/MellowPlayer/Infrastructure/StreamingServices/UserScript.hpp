#pragma once

#include <MellowPlayer/Application/StreamingServices/UserScriptBase.hpp>

namespace MellowPlayer::Infrastructure
{
    class UserScript : public Application::UserScriptBase
    {
    public:
        void import(const QString& path) override;
        void load(const QString& path) override;
    };
}
