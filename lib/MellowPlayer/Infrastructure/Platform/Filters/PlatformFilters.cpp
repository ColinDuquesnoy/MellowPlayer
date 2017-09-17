#include "PlatformFilters.hpp"
#include "TokenizedFilters.hpp"
#include "IPlatformFilter.hpp"
#include "PlatformFilterFactory.hpp"

using namespace MellowPlayer::Infrastructure;

PlatformFilters::PlatformFilters(IPlatformFilterFactory& filterFactory): filtersFactory_(filterFactory)
{

}

bool PlatformFilters::match(const QString& filtersString) const
{
    for(auto filter: TokenizedFilters(filtersString)) {
        auto platformFilter = filtersFactory_.create(filter);
        if (platformFilter->match())
            return true;
    }

    return false;
}

