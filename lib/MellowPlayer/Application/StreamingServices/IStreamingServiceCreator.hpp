#pragma once

#include <MellowPlayer/Macros.hpp>
#include <QtCore/QString>

BEGIN_MELLOWPLAYER_NAMESPACE(Application)

class IStreamingServiceCreator {
public:
    virtual ~IStreamingServiceCreator() = default;

    virtual QString create(const QString& serviceName,
                           const QString& serviceUrl,
                           const QString& authorName,
                           const QString& authorWebsite) const = 0;
};

END_MELLOWPLAYER_NAMESPACE
