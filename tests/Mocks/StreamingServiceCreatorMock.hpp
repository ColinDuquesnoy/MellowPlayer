#pragma once
#include <MellowPlayer/Application/StreamingServices/IStreamingServiceCreator.hpp>
#include <fakeit.hpp>
#include <memory>

using namespace MellowPlayer::Application;
using namespace fakeit;

class StreamingServiceCreatorMock
{
public:
    static Mock<IStreamingServiceCreator> get()
    {
        Mock<IStreamingServiceCreator> mock;
        When(Method(mock, create)).AlwaysReturn("/tmp/pluginDir");
        return mock;
    }
};
