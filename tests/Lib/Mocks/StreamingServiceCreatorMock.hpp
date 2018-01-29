#pragma once
#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceCreator.hpp>
#include <fakeit/fakeit.hpp>
#include <memory>

using namespace MellowPlayer::Domain;
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
