#pragma once
#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/Application/StreamingServices/IStreamingServiceCreator.hpp>

USING_MELLOWPLAYER_NAMESPACE(Application)
using namespace fakeit;

class StreamingServiceCreatorMock {
public:
    static Mock<IStreamingServiceCreator> get() {
        Mock<IStreamingServiceCreator> mock;
        When(Method(mock, create)).AlwaysReturn("/tmp/pluginDir");
        return mock;
    }
};

