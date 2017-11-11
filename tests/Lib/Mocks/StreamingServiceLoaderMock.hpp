#pragma once

#include <MellowPlayer/Domain/StreamingServices/IStreamingServiceLoader.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingService.hpp>
#include <MellowPlayer/Domain/StreamingServices/StreamingServiceMetadata.hpp>
#include <QList>
#include <catch.hpp>
#include <fakeit.hpp>
#include <memory>

namespace MellowPlayer { namespace Domain { struct Theme; } }

using namespace MellowPlayer::Domain;
using namespace MellowPlayer::Domain;
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
