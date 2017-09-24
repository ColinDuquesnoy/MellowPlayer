#pragma once

#include <MellowPlayer/Application/UserScripts/UserScriptBase.hpp>
#include <QtCore/QString>

#define FAKE_USER_SCRIPT_CODE "foo"

namespace MellowPlayer::Application::Tests
{
    class FakeUserScript: public UserScriptBase
    {
    public:
        bool import(const QString& path) override
        {
            return load(path);
        }

        bool load(const QString& path) override
        {
            UserScriptBase::path_ = path;
            Application::UserScriptBase::code_ = FAKE_USER_SCRIPT_CODE;
            return true;
        }
    };
}