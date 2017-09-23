#include "FakeUserScript.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application::Tests;


bool FakeUserScript::import(const QString& path)
{
    return load(path);
}

bool FakeUserScript::load(const QString& path)
{
    UserScriptBase::path_ = path;
    Application::UserScriptBase::code_ = FAKE_USER_SCRIPT_CODE;
    return true;
}
