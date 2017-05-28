#pragma once

#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/UseCases/Interfaces/IStreamingServicePluginLoader.hpp>
#include <MellowPlayer/Entities/StreamingServices/StreamingServicePlugin.hpp>

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace std;
using namespace fakeit;

class PluginLoaderMock {
public:
    static Mock<IStreamingServicePluginLoader> get() {
        Mock<IStreamingServicePluginLoader> mock;
        When(Method(mock, load)).AlwaysDo([]() {
            QList<shared_ptr<StreamingServicePlugin>> list;
            list.append(createPlugin("Deezer"));
            list.append(createPlugin("Spotify"));
            return list;
        });
        return mock;
    }

    static StreamingServiceStyle PLUGIN_STYLE;

private:
    static unique_ptr<StreamingServicePlugin> createPlugin(const QString& name) {
        StreamingServicePluginMetadata metadata;
        metadata.name = name;
        metadata.url = "http://" + name.toLower() + ".com";
        return make_unique<StreamingServicePlugin>(metadata, PLUGIN_STYLE);
    }
};
