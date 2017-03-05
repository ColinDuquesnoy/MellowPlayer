#pragma once

#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/UseCases/IStreamingServicesLoader.hpp>
#include "ApplicationSettingsMock.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace std;
using namespace fakeit;

class StreamingServiceLoaderMock{
public:
    static Mock<IStreamingServicesLoader> get() {
        Mock<IStreamingServicesLoader> mock;
        When(Method(mock, load)).AlwaysDo([]() {
            StreamingServicesList list;
            list.append(createStreamingService("Deezer"));
            list.append(createStreamingService("Spotify"));
            return list;
        });
        return mock;
    }

private:
    static unique_ptr<StreamingService> createStreamingService(const QString& name) {
        static auto applicationSettingsMock = ApplicationSettingsMock::get();
        PluginMetadata metadata;
        metadata.name = name;
        metadata.url = "http://" + name.toLower() + ".com";
        auto plugin = make_unique<StreamingService>(metadata, applicationSettingsMock.get());
        return plugin;
    }
};
