#include <MellowPlayer/Infrastructure/Updater/Release.hpp>
#include <MellowPlayer/Infrastructure/BuildConfig.hpp>

using namespace MellowPlayer::Infrastructure;

Release Release::current_(BuildConfig::getVersion(), QDate::fromString(BuildConfig::getBuildDate(), Qt::ISODate));

Release::Release(const QString& name, const QDate& date, QObject* parent)
        : QObject(parent), url_(""), name_(name), date_(date), preRelease_(false), assets_()
{

}

Release::Release(const QString& url, const QString& name, const QDate& date, const AssetList& assets, bool preRelease, QObject* parent)
        : QObject(parent), url_(url), name_(name), date_(date), preRelease_(preRelease), assets_(assets)
{

}

QString Release::url() const
{
    return url_;
}

QString Release::name() const
{
    return name_;
}

QString Release::date() const
{
    return date_.toString("MMMM dd yyyy");
}

bool Release::isPreRelease() const
{
    return preRelease_;
}

const AssetList& Release::assets() const
{
    return assets_;
}

bool Release::operator==(const Release& other) const
{
    return date_ == other.date_;
}

bool Release::operator!=(const Release& other) const
{
    return !operator==(other);
}

bool Release::operator>(const Release& other) const
{
    return date_ > other.date_;
}

bool Release::operator>=(const Release& other) const
{
    return date_ >= other.date_;
}

bool Release::operator<(const Release& other) const
{
    return date_ < other.date_;
}

bool Release::operator<=(const Release& other) const
{
    return date_ <= other.date_;
}

const Release& Release::current()
{
    return current_;
}

bool Release::isValid() const
{
    bool isValid = !date().isEmpty() && !name().isEmpty();

    if (isValid && !url_.isEmpty()) {
        bool haveAppImage = false;
        bool haveWindowsInstaller = false;
        bool haveDmg = false;

        for (auto& asset : assets_) {
            if (asset.isDmg())
                haveDmg = true;
            if (asset.isAppImage())
                haveAppImage = true;
            if (asset.isWindowsInstaller())
                haveWindowsInstaller = true;
        }

        return haveAppImage && haveDmg && haveWindowsInstaller;
    }

    return isValid;
}
