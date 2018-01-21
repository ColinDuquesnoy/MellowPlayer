#include <MellowPlayer/Infrastructure/PlatformFilters/FilterConverter.hpp>

using namespace MellowPlayer::Infrastructure;

FilterConverter::FilterConverter():
    linux_("Linux"),
    appImage_("AppImage"),
    windows_("Windows"),
    osx_("OSX"),
    all_("All")
{

}

QString FilterConverter::toString(Filter filter) const
{
    QString filterString;

    switch (filter) {
        case Filter::Linux:
            filterString = linux_;
            break;
        case Filter::AppImage:
            filterString = appImage_;
            break;
        case Filter::OSX:
            filterString = osx_;
            break;
        case Filter::Windows:
            filterString = windows_;
            break;
        case Filter::All:
            filterString = all_;
            break;
    }

    return filterString;
}

Filter FilterConverter::fromString(const QString& filterString) const
{
    QString lowerCaseFilter = filterString.toLower().trimmed();

    if (lowerCaseFilter == linux_.toLower())
        return Filter::Linux;
    else if (lowerCaseFilter == appImage_.toLower())
        return Filter::AppImage;
    else if (lowerCaseFilter == windows_.toLower())
        return Filter::Windows;
    else if (lowerCaseFilter == osx_.toLower())
        return Filter::OSX;
    else
        return Filter::All;
}
