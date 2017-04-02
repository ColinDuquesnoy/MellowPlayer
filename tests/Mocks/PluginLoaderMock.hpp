#pragma once

#include <fakeit.hpp>
#include <memory>
#include <MellowPlayer/UseCases/Interfaces/IPluginLoader.hpp>
#include <MellowPlayer/Entities/Plugin.hpp>

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace std;
using namespace fakeit;

class PluginLoaderMock {
public:
    static Mock<IPluginLoader> get() {
        Mock<IPluginLoader> mock;
        When(Method(mock, load)).AlwaysDo([]() {
            PluginList list;
            list.append(createPlugin("Deezer"));
            list.append(createPlugin("Spotify"));
            return list;
        });
        return mock;
    }

    static PluginStyle PLUGIN_STYLE;

private:
    static unique_ptr<Plugin> createPlugin(const QString& name) {
        PluginMetadata metadata;
        metadata.name = name;
        metadata.url = "http://" + name.toLower() + ".com";
        return make_unique<Plugin>(metadata, PLUGIN_STYLE);
    }
};
