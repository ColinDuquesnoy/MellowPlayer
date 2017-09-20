#include "PlatformFilterFactory.hpp"
#include "AllFilter.hpp"
#include "AppImageFilter.hpp"
#include "LinuxFilter.hpp"
#include "OsxFilter.hpp"
#include "WindowsFilter.hpp"

using namespace std;
using namespace MellowPlayer::Infrastructure;

unique_ptr<IPlatformFilter> PlatformFilterFactory::create(Filter filter) const
{
    switch (filter) {
        case Filter::All:
            return make_unique<AllFilter>();
        case Filter::AppImage:
            return make_unique<AppImageFilter>();
        case Filter::Linux:
            return make_unique<LinuxFilter>();
        case Filter::Windows:
            return make_unique<WindowsFilter>();
        case Filter::OSX:
            return make_unique<OsxFilter>();
    }    
    return nullptr;
}
