#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/Application/StreamingServices/IStreamingServiceWatcher.hpp>

using namespace MellowPlayer::Application;
using namespace fakeit;

class StreamingServiceWatcherMock {
public:
    static Mock<IStreamingServiceWatcher> get() {
        Mock<IStreamingServiceWatcher> mock;
        When(Method(mock, watch)).AlwaysDo([](StreamingService&){ });
        return mock;
    }
};

