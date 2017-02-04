#include "PluginLoaderMock.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace std;
using namespace fakeit;

unique_ptr<Plugin> createPlugin(const QString& name) {
    PluginMetadata metadata;
    metadata.name = name;
    metadata.url = "http://" + name.toLower() + ".com";
    auto plugin = make_unique<Plugin>(metadata);
    return plugin;
}

Mock<IPluginLoader> PluginLoaderMock::basicMock() {
    Mock<IPluginLoader> mock;
    When(Method(mock, loadPlugins)).AlwaysDo([]() {
        PluginList list;
        list.append(createPlugin("Deezer"));
        list.append(createPlugin("Spotify"));

        return list;
    });
    return mock;
}
