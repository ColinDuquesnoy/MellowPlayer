#include "PluginLoaderMock.hpp"

USE_MELLOWPLAYER_NAMESPACE(Entities)
USE_MELLOWPLAYER_NAMESPACE(UseCases)
using namespace std;
using namespace fakeit;

Plugin createPlugin(const QString& name) {
    Plugin plugin;
    plugin.name = name;
    plugin.url = "http://" + name.toLower() + ".com";

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
