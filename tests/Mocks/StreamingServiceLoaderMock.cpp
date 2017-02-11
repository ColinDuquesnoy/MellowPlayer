#include "StreamingServiceLoaderMock.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace std;
using namespace fakeit;

unique_ptr<StreamingService> createStreamingService(const QString& name) {
    PluginMetadata metadata;
    metadata.name = name;
    metadata.url = "http://" + name.toLower() + ".com";
    auto plugin = make_unique<StreamingService>(metadata);
    return plugin;
}

Mock<IStreamingServicesLoader> StreamingServiceLoaderMock::basicMock() {
    Mock<IStreamingServicesLoader> mock;
    When(Method(mock, load)).AlwaysDo([]() {
        StreamingServicesList list;
        list.append(createStreamingService("Deezer"));
        list.append(createStreamingService("Spotify"));

        return list;
    });
    return mock;
}
