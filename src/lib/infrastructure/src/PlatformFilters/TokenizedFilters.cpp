#include <MellowPlayer/Infrastructure/PlatformFilters/TokenizedFilters.hpp>
#include <MellowPlayer/Infrastructure/PlatformFilters/FilterConverter.hpp>

using namespace MellowPlayer::Infrastructure;

#define PLATFORM_FILTER_SEPARATOR "-"

TokenizedFilters::TokenizedFilters(const QString& filters)
{
    QStringList tokens = filters.toLower().split(PLATFORM_FILTER_SEPARATOR);
    FilterConverter converter;

    for (auto token: tokens)
        filters_.append(converter.fromString(token));
}

TokenizedFilters::TokenizedFilters(const QList<Filter>& filters): filters_(filters)
{

}

QString TokenizedFilters::join() const
{
    QStringList strings;
    FilterConverter converter;

    for(auto filter: filters_) {
        strings.append(converter.toString(filter));
    }

    return strings.join(PLATFORM_FILTER_SEPARATOR);
}

TokenizedFilters::const_iterator TokenizedFilters::begin(void) const
{
    return filters_.begin();
}

TokenizedFilters::const_iterator TokenizedFilters::end(void) const
{
    return filters_.end();
}
