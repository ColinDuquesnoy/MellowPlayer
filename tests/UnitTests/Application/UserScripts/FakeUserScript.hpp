#pragma once

#include <MellowPlayer/Application/UserScripts/UserScriptBase.hpp>
#include <QtCore/QString>

#define FAKE_USER_SCRIPT_CODE "foo"

namespace MellowPlayer::Application::Tests
{
    class FakeUserScript: public UserScriptBase
    {
    public:
        bool import(const QString& path) override;
        bool load(const QString& path) override;
    };
}