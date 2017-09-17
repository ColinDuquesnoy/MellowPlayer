#pragma once

#include <QString>

namespace MellowPlayer::Infrastructure
{
    class IPlatformFilters
    {
    public:
        virtual ~IPlatformFilters() = default;
        virtual bool match(QString) const = 0;
    };

    class PlatformFilters: public IPlatformFilters
    {
    public:
        bool match(QString filters) const override;
    };
}
