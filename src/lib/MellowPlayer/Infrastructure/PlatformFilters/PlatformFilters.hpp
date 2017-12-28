#pragma once

#include <QString>

namespace MellowPlayer::Infrastructure
{
    class PlatformFilters
    {
    public:
        bool match(const QString& filters) const;
    };
}
