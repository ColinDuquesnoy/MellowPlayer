#include "Asset.hpp"
#include <QtCore/QUrl>

using namespace MellowPlayer::Application;

Asset::Asset() : Asset("", "")
{
}

Asset::Asset(const QString& name, const QString& url) : name_(name), url_(url)
{
}

QString Asset::getName() const
{
    return name_;
}

QString Asset::getUrl() const
{
    return url_;
}

bool Asset::isAppImage() const
{
    return name_.endsWith(".AppImage");
}

bool Asset::isWindowsInstaller() const
{
    return name_.endsWith("_Setup.exe");
}

bool Asset::isDmg() const
{
    return name_.endsWith(".dmg");
}

bool Asset::isValid() const
{
    return QUrl(url_).isValid() && (isAppImage() || isWindowsInstaller() || isDmg());
}
