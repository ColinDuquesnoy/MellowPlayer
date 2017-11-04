#pragma once
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceWatcher.hpp>
#include <fakeit.hpp>
#include <memory>

using namespace MellowPlayer::Domain;
using namespace fakeit;

class StreamingServiceWatcherMock
{
public:
    static Mock<IStreamingServiceWatcher> get()
    {
        Mock<IStreamingServiceWatcher> mock;
        When(Method(mock, watch)).AlwaysDo([](StreamingService&) {});
        return mock;
    }
};
