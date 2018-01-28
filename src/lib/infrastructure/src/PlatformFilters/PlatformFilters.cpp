#include <MellowPlayer/Infrastructure/PlatformFilters/PlatformFilters.hpp>
#include <MellowPlayer/Infrastructure/PlatformFilters/TokenizedFilters.hpp>
#include <MellowPlayer/Infrastructure/PlatformFilters/IPlatformFilter.hpp>
#include <MellowPlayer/Infrastructure/PlatformFilters/PlatformFilterFactory.hpp>

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

