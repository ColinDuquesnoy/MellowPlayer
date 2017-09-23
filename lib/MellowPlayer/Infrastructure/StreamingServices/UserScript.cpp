#include "UserScript.hpp"

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Infrastructure;

void UserScript::import(const QString& path)
{
    qDebug() << "importing" << path;
}

void UserScript::load(const QString& path)
{
    qDebug() << "loading" << path;
    path_ = path;
}
