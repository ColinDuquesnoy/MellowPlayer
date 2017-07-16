#include "Release.hpp"
#include <QDebug>

using namespace MellowPlayer::Application;

Release Release::current_(MELLOWPLAYER_VERSION,
                          QDate::fromString(QString(__DATE__).simplified(), "MMM d yyyy"));

Release::Release(const QString& name, const QDate& date, QObject* parent) :
        QObject(parent),
        url_(""),
        name_(name),
        date_(date),
        description_(""),
        preRelease_(false),
        assets_() {

}

Release::Release(const QString& url, const QString& version, const QDate& date, const QString& description,
                 const AssetList& assets, bool preRelease, QObject* parent) :
        QObject(parent),
        url_(url),
        name_(version),
        date_(date),
        description_(description),
        preRelease_(preRelease),
        assets_(assets) {
}

QString Release::getName() const {
    return name_;
}

QString Release::getDate() const {
    return date_.toString("MMMM dd yyyy");
}

const QString& Release::getDescription() const {
    return description_;
}

bool Release::isPreRelease() const {
    return preRelease_;
}

const AssetList& Release::getAssets() const {
    return assets_;
}

bool Release::operator==(const Release& other) const {
    return date_ == other.date_;
}

bool Release::operator!=(const Release& other) const {
    return !operator==(other);
}

bool Release::operator>(const Release& other) const {
    return date_ > other.date_;
}

bool Release::operator>=(const Release& other) const {
    return date_ >= other.date_;
}

bool Release::operator<(const Release& other) const {
    return date_ < other.date_;
}

bool Release::operator<=(const Release& other) const {
    return date_ <= other.date_;
}

const Release& Release::current() {
    return current_;
}

bool Release::isValid() const {
    bool isValid = !getDate().isEmpty() && !getName().isEmpty();

    if (isValid && !url_.isEmpty()) {
        bool haveAppImage = false;
        bool haveWindowsInstaller = false;
        bool haveDmg = false;

        for(auto& asset: assets_) {
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
