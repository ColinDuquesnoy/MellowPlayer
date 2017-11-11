#pragma once

#include <QString>
#include <MellowPlayer/Domain/Plugins/WebPlayerScript.hpp>

namespace MellowPlayer::Domain::Tests
{
    class FakeWebPlayerScript: public WebPlayerScript
    {
    public:
        FakeWebPlayerScript(QString code)
        {
            code_ = std::move(code);
        }
        void load() override { };
    };
}