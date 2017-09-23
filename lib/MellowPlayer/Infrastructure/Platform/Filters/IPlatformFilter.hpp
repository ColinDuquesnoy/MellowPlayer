#pragma once

#include <QtCore/QString>

namespace MellowPlayer::Infrastructure
{
    class IPlatform;

    class IPlatformFilter
    {
    public:
        virtual ~IPlatformFilter() = default;

        virtual bool match() const = 0;
    };
}
