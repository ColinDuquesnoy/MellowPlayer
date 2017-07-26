#pragma once

#include <MellowPlayer/Application/StreamingServices/IStreamingServiceLoader.hpp>
#include <MellowPlayer/Application/StreamingServices/StreamingService.hpp>
#include <QList>
#include <fakeit.hpp>
#include <memory>

using namespace MellowPlayer::Application;
using namespace MellowPlayer::Application;
using namespace std;
using namespace fakeit;

class StreamingServiceLoaderMock
{
public:
    static Mock<IStreamingServiceLoader> get()
    {
        Mock<IStreamingServiceLoader> mock;
        When(Method(mock, load)).AlwaysDo([]() {
            QList<shared_ptr<StreamingService>> list;
            list.append(createPlugin("Deezer"));
            list.append(createPlugin("Spotify"));
            list.append(createPlugin("Mixcloud"));
            list.append(createPlugin("Soundcloud"));
            return list;
        });
        return mock;
    }

    static Theme DEFAULT_theme;

private:
    static unique_ptr<StreamingService> createPlugin(const QString& name)
    {
        StreamingServiceMetadata metadata;
        metadata.name = name;
        metadata.url = "http://" + name.toLower() + ".com";
        return make_unique<StreamingService>(metadata, DEFAULT_theme);
    }
};
