#pragma once
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceWatcher.hpp>
#include <memory>


namespace MellowPlayer::Domain::Tests
{
    class FakeStreamingServiceWatcher : public IStreamingServiceWatcher
    {
    public:
        void watch(StreamingService& serviceToWatch) override
        {
            watchedServices.append(&serviceToWatch);
        }

        QList<StreamingService*> watchedServices;
    };
}