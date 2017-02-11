#pragma once

#include <MellowPlayer/Macros.hpp>
#include <MellowPlayer/Entities/StreamingService.hpp>

BEGIN_MELLOWPLAYER_NAMESPACE(UseCases)

class IStreamingServicesLoader: public NonCopyable {
public:
    virtual ~IStreamingServicesLoader() = default;

    virtual Entities::StreamingServicesList load() const = 0;
};

END_MELLOWPLAYER_NAMESPACE
