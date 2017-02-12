#pragma once

#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/UseCases/StreamingService.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class IStreamingServicesLoader: public QObject {
public:
    virtual ~IStreamingServicesLoader() = default;

    virtual StreamingServicesList load() const = 0;
};

END_MELLOWPLAYER_NAMESPACE
