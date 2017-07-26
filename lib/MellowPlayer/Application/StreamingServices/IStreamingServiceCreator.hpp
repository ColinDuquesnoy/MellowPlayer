#pragma once

#include <QtCore/QString>

namespace MellowPlayer::Application
{
    class IStreamingServiceCreator
    {
    public:
        virtual ~IStreamingServiceCreator() = default;

        virtual QString create(const QString& serviceName, const QString& serviceUrl, const QString& authorName,
                               const QString& authorWebsite) const = 0;
    };
}
