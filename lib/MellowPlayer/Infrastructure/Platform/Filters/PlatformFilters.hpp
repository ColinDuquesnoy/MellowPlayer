#pragma once

#include <QString>

namespace MellowPlayer::Infrastructure
{
    class IPlatformFilterFactory;

    class IPlatformFilters
    {
    public:
        virtual ~IPlatformFilters() = default;
        virtual bool match(const QString& filters) const = 0;
    };

    class PlatformFilters: public IPlatformFilters
    {
    public:
        explicit PlatformFilters(IPlatformFilterFactory& filterFactory);
        bool match(const QString& filters) const override;

    private:
        IPlatformFilterFactory& filtersFactory_;
    };
}
