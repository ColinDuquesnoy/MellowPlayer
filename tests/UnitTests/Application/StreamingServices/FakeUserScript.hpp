#pragma once

#include <MellowPlayer/Application/StreamingServices/UserScriptBase.hpp>
#include <QtCore/QString>

#define FAKE_USER_SCRIPT_CODE "foo"

namespace MellowPlayer::Application::Tests
{
    class FakeUserScript: public UserScriptBase
    {
    public:
        void import(const QString& path) override;

        void load(const QString& path) override;
    };
}