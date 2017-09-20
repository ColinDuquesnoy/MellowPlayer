#include "FakeUserScript.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application::Tests;


void FakeUserScript::import(const QString& path)
{
    load(path);
}

void FakeUserScript::load(const QString& path)
{
    UserScriptBase::path_ = path;
    Application::UserScriptBase::code_ = FAKE_USER_SCRIPT_CODE;
}
