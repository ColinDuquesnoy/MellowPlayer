#include "PlatformFilters.hpp"
#include "TokenizedFilters.hpp"
#include "IPlatformFilter.hpp"
#include "PlatformFilterFactory.hpp"

using namespace MellowPlayer::Infrastructure;

bool PlatformFilters::match(const QString& filtersString) const
{
    PlatformFilterFactory filtersFactory;
    TokenizedFilters filters(filtersString);
    
    for(auto filter: filters) {
        auto platformFilter = filtersFactory.create(filter);
        if (platformFilter->match())
            return true;
    }
    
    return false;
}

